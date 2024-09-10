//
// Saves the current image
//
HRESULT SimpleImage::Save(__in IShellItem *saveAsItem)
{
    ComPtr<IWICImagingFactory> wicFactory;
    ComPtr<ID2D1Factory> d2dFactory;
    ComPtr<IWICBitmap> wicBitmap;
    ComPtr<ID2D1RenderTarget> wicRenderTarget;

    // Clear backup information from previous save
    m_imageInfo.backupFileName.clear();

    // Don't save if there are no image operations applied to this image unless the user specifed 'Save As'
    if (m_imageOperations.empty() && nullptr == saveAsItem)
    {
        return S_OK;
    }

    HRESULT hr = Direct2DUtility::GetWICFactory(&wicFactory);
    if (SUCCEEDED(hr))
    {
        hr = Direct2DUtility::GetD2DFactory(&d2dFactory);
    }

    // Get the original bitmap rectangle in terms of the current crop
    D2D1_RECT_F originalBitmapRect =
        D2D1::RectF(0, 0, Direct2DUtility::GetRectWidth(m_clipRect), Direct2DUtility::GetRectHeight(m_clipRect));

    // Adjust height and width based on current orientation and clipping rectangle
    float width = m_isHorizontal ? Direct2DUtility::GetRectWidth(m_clipRect) : Direct2DUtility::GetRectHeight(m_clipRect);
    float height = m_isHorizontal ? Direct2DUtility::GetRectHeight(m_clipRect) : Direct2DUtility::GetRectWidth(m_clipRect);

    if (SUCCEEDED(hr))
    {
        // Create WIC bitmap for rendering
        hr = wicFactory->CreateBitmap(
            static_cast<unsigned int>(width),
            static_cast<unsigned int>(height),
            GUID_WICPixelFormat32bppBGR,
            WICBitmapCacheOnLoad,
            &wicBitmap);
    }

    if (SUCCEEDED(hr))
    {
        hr = d2dFactory->CreateWicBitmapRenderTarget(wicBitmap, D2D1::RenderTargetProperties(), &wicRenderTarget);
    }

    if (SUCCEEDED(hr))
    {
        // Replace current bitmap with one that's compatible with the WIC render target
        if (m_bitmap)
        {
            m_bitmap = nullptr;
        }
        
        hr = Direct2DUtility::LoadBitmapFromFile(wicRenderTarget, m_imageInfo.fileName.c_str(), 0, 0, &m_bitmap);
    }

    if (SUCCEEDED(hr))
    {
        // When rotating images make sure that the point around which rotation occurs lines
        // up with the center of the rotated render target
        if (false == m_isHorizontal)
        {
            float offsetX;
            float offsetY;

            if (width > height)
            {
                offsetX = (width - height) / 2;
                offsetY = -offsetX;
            }
            else
            {
                offsetY = (height - width) / 2;
                offsetX = - offsetY;
            }

            D2D1_MATRIX_3X2_F translation = D2D1::Matrix3x2F::Translation(offsetX, offsetY);
            wicRenderTarget->SetTransform(translation);
        }

        // Update current render target to point to WIC render target
        m_currentRenderTarget = wicRenderTarget;

        // Draw updated image to WIC render target
        wicRenderTarget->BeginDraw();
        DrawImage(originalBitmapRect, m_clipRect, true);
        wicRenderTarget->EndDraw();
    }

    if (SUCCEEDED(hr) && !m_imageOperations.empty())
    {
        // Create copy of original image unless the user is simply using 'Save As'
        std::wstring backupPath(m_imageInfo.fileName);
        backupPath.insert(backupPath.find_last_of('\\'), L"\\AnnotatorBackup");

        std::wstring backupDirectory(backupPath.substr(0, backupPath.find_last_of('\\')));

        // Create backup directory if needed
        if (false == ::CreateDirectoryW(backupDirectory.c_str(), nullptr))
        {
            hr = (GetLastError() == ERROR_ALREADY_EXISTS) ? S_OK : E_FAIL;
        }
    
        if (SUCCEEDED(hr))
        {
            // Do not copy if the backup file already exists
            if (false == ::CopyFile(m_imageInfo.fileName.c_str(), backupPath.c_str(), true))
            {
                hr = (GetLastError() == ERROR_FILE_EXISTS) ? S_OK : E_FAIL;
            }
            else
            {
                // Capture name of backup file
                m_imageInfo.backupFileName.assign(backupPath);
            }
        }
    }

    if (SUCCEEDED(hr))
    {
        if (nullptr == saveAsItem)
        {
            // Save updated file
            hr = Direct2DUtility::SaveBitmapToFile(wicBitmap, m_imageInfo.fileName.c_str());
        }
        else
        {
            // Save updated file as the specifed shell item
            wchar_t * saveAsFileName;
            hr = saveAsItem->GetDisplayName(SIGDN_FILESYSPATH, &saveAsFileName);

            if (SUCCEEDED(hr))
            {
                hr = Direct2DUtility::SaveBitmapToFile(wicBitmap, m_imageInfo.fileName.c_str(), saveAsFileName);

                ::CoTaskMemFree(saveAsFileName);
            }
        }
    }

    if (SUCCEEDED(hr))
    {
        // Force image to reload
        hr = DiscardResources();
        m_isHorizontal = true;

        if (nullptr == saveAsItem)
        {
            // Clear all undo operations
            m_imageOperations.clear();

            // Empty redo stack
            while (!m_redoStack.empty())
            {
                m_redoStack.pop();
            }
        }
    }

    return hr;
}
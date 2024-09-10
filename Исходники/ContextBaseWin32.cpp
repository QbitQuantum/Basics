		//---------------------------------------------------------------------------------
		bool ContextBaseWin32::selfDestroy(){
			if (mHRC){								// Si tenemos un contexto de renderizado
				if (!wglMakeCurrent(NULL, NULL)){		// Comprobamos si podemos librerar el Device context y el render context.
					MessageBoxA(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				}
				if (!wglDeleteContext(mHRC)){		// Podemos eliminar el render context?
					MessageBoxA(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				}
				mHRC = NULL;                           // Set RC To NULL
			}

			// Intentamos liberar ahora el device context
			if (mHDC && !ReleaseDC(mHWnd, mHDC)){				// Podemos liberar el device context?
				MessageBoxA(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				mHDC = NULL;									// Set DC To NULL
			}

			// Ahora toca cerrar la ventana
			if (mHWnd && !DestroyWindow(mHWnd)){				// Are We Able To Destroy The Window?
				MessageBoxA(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				mHWnd = NULL;									// Set hWnd To NULL
			}

			// Por ultimo hay que "desregistar" la clase de ventana y asi podremos borrar adecuadamente la misma para poder reabrirla más tarde.
			if (!UnregisterClassA("OpenGL", mHInstance)){		// Are We Able To Unregister Class
				MessageBoxA(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
				mHInstance = NULL;								// Set hInstance To NULL
			}


			return true;
		}
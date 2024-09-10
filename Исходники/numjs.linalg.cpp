/**
  *  Dot:
  *  Dot product of two arrays.
  *  For 2-D arrays it is equivalent to matrix multiplication, and for 1-D arrays to inner product of vectors
  * (without complex conjugation).
  *
  *  arguments:
  *  info[0]: Number represent the number of rows of the left matrix.
  *  info[1]: Number represent the number of columns of the left matrix.
  *  info[2]: Buffer(object created by smalloc) represent the left numjs.Matrix object .
  *  info[3]: Number represent the number of rows of the right matrix.
  *  info[4]: Number represent the number of columns of the right matrix.
  *  info[5]: Buffer(object created by smalloc) represent the right numjs.Matrix object .
  *  info[6]: Buffer(object created by smalloc) for return value, which is the dot product of
  *           left matrix and right matrix.
*/
void Dot(const Nan::FunctionCallbackInfo<v8::Value>& info){
    using CMd = Eigen::Map <const Eigen::MatrixXd >;
    using Md = Eigen::Map <Eigen::MatrixXd >;

	if (info.Length() < 7) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}

    if (!info[0]->IsUint32() || !info[1]->IsUint32() ||
    	!info[3]->IsUint32() || !info[4]->IsUint32()) {
    	Nan::ThrowTypeError("Wrong arguments");
        return;
    }

	if (info[2]->IsNumber()) {
	    double leftParam(info[2]->NumberValue());

	    if(!info[5]->IsNumber()){
            Local<Object> rightBuffer = info[5].As<Object>();

            if (rightBuffer->HasIndexedPropertiesInExternalArrayData()) {
                double *refRightData = static_cast<double*>(rightBuffer->GetIndexedPropertiesExternalArrayData());
                size_t rowsRight(info[3]->Uint32Value());
                size_t colsRight(info[4]->Uint32Value());
                CMd rightMat(refRightData, rowsRight, colsRight);

                Local<Object> resBuffer = info[6].As<Object>();
                if (resBuffer->HasIndexedPropertiesInExternalArrayData()) {
                    double *refResData = static_cast<double*>(resBuffer->GetIndexedPropertiesExternalArrayData());
                    Md res(refResData, rowsRight, colsRight);
                    res = leftParam * rightMat;

                    Local<Boolean> b = Nan::New(true);
                    info.GetReturnValue().Set(b);
                }
            }
        }
    }
	else{
	    Local<Object> leftBuffer = info[2].As<Object>();
	    if (leftBuffer->HasIndexedPropertiesInExternalArrayData()) {
	        double *refLeftData = static_cast<double*>(leftBuffer->GetIndexedPropertiesExternalArrayData());
	        size_t rowsLeft(info[0]->Uint32Value());
            size_t colsLeft(info[1]->Uint32Value());
            CMd leftMat(refLeftData, rowsLeft, colsLeft);

            if(info[5]->IsNumber()){
                double rightParam(info[5]->NumberValue());
                Local<Object> resBuffer = info[6].As<Object>();
                if (resBuffer->HasIndexedPropertiesInExternalArrayData()) {
                    double *refResData = static_cast<double*>(resBuffer->GetIndexedPropertiesExternalArrayData());
                    Md res(refResData, rowsLeft, colsLeft);
                    res = leftMat * rightParam;
                    Local<Boolean> b = Nan::New(true);
                    info.GetReturnValue().Set(b);
                }
            }
            else{
                Local<Object> rightBuffer = info[5].As<Object>();
                if (rightBuffer->HasIndexedPropertiesInExternalArrayData()) {
                    double *refRightData = static_cast<double*>(rightBuffer->GetIndexedPropertiesExternalArrayData());
                	size_t rowsRight(info[3]->Uint32Value());
                    size_t colsRight(info[4]->Uint32Value());
                    CMd rightMat(refRightData, rowsRight, colsRight);

                    Local<Object> resBuffer = info[6].As<Object>();
                    if (resBuffer->HasIndexedPropertiesInExternalArrayData()) {
                        double *refResData = static_cast<double*>(resBuffer->GetIndexedPropertiesExternalArrayData());
                        Md res(refResData, rowsLeft, colsRight);
                         res = leftMat * rightMat;
                        Local<Boolean> b = Nan::New(true);
                        info.GetReturnValue().Set(b);
                    }
                }
            }
	    }
	    else{
	        Nan::ThrowTypeError("Wrong type of the first argument");
            return;
	    }

	    Local<Boolean> b = Nan::New(false);
        info.GetReturnValue().Set(b);
	}
}
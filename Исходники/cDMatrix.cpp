void LapackInvAndDet(cDMatrix& theMatrix, cDMatrix& theInvMatrix, double& theDet)
{
uint myNCol = theMatrix.GetNCols() ;

double  *myAP = new double[myNCol*(myNCol + 1)/2],
                *myW = new double[myNCol],
                *myZ = new double[myNCol*myNCol],
                *myWork = new double[myNCol * 3] ;
int myInfo,
        myN = (int)(myNCol),
        myldz = (int)(myNCol) ;

        for (register int i = 0 ; i < myN ; i++)
                for (register int j = i ; j < myldz ; j++)
                        myAP[i+(j+1)*j/2]  = theMatrix[i][j] ;

        F77_NAME(dspev)("V", "U", &myN, myAP, myW, myZ, &myldz, myWork, &myInfo) ;

        if (myInfo != 0)
                throw cOTError("Non inversible matrix") ;
        theDet = 1.0L ;
cDVector myInvEigenValue = cDVector(myNCol) ;

cDMatrix myEigenVector(myNCol, myNCol) ;
        for (register uint i = 0 ; i < myNCol ; i++)
        {       theDet *= myW[i] ;
                myInvEigenValue[i] = 1.0 /myW[i] ;
                for (register int j = 0 ; j < myN ; j++)
                        myEigenVector[i][j] = myZ[i + j*myN] ;
        }
        theInvMatrix =  myEigenVector ;
cDMatrix myAuxMat1 = Diag(myInvEigenValue), myAuxMat2 = Transpose(myEigenVector) ;
cDMatrix myAuxMat = myAuxMat1 * myAuxMat2 ;
        theInvMatrix = theInvMatrix * myAuxMat ;
        
        delete myAP ;
        delete myW ;
        delete myZ ;
        delete myWork ;
}
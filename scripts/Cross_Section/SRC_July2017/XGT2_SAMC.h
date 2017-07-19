//#include "XGT2_XEMC.h"
/*XGT2_VAR* gGet_XS_SAMC_SUM(TChain* aTree){{{*/
XGT2_VAR* gGet_XS_SAMC_SUM(TChain* aTree,const Double_t aBin,const Double_t aBinCut, const Double_t aAccCut[9], const Double_t aVZ_Cut[2], const TString &aArm, const TString &aTarget, const TString &aKin, const Double_t aP0, const Double_t aAngle, const TString& aBin_Variable, double *aBinCor, const Double_t aI_avg, Get_XS* aXS)
{
	/* Bin Cuts:
	   |Dp_tg -aBin| < aCut;
	   Acc Cuts:
	   |x_fp|       < aAccCut[0];
	   |y_fp|       < aAccCut[1];
	   |th_fp|      < aAccCut[2];
	   |ph_fp|      < aAccCut[3];
	   |dp_rec|     < aAccCut[4];
	   |y_tg_rec|   < aAccCut[5];
	   |th_tg_rec|  < aAccCut[6];
	   |ph_tg_rec|  < aAccCut[7];
	   |reactz_rec| < aAccCut[8];
Weight:
w[i] = aCS_Center / aCS[i];
*/
	XGT2_VAR* sum = new XGT2_VAR();

	Int_t aNevt = aTree->GetEntries();
	Double_t x_fp,y_fp,th_fp,ph_fp,dp_rec,y_tg_rec,th_tg_rec,ph_tg_rec,reactz_rec,Angle_rec;
	Double_t E_s,E_p, Theta, Qsq,Xbj;
	Int_t aIsPassed; 

	aTree->SetBranchAddress("x_fp",         &x_fp);
	aTree->SetBranchAddress("y_fp",         &y_fp);
	aTree->SetBranchAddress("th_fp",        &th_fp);
	aTree->SetBranchAddress("ph_fp",        &ph_fp);
	aTree->SetBranchAddress("dp_rec",       &dp_rec);
	aTree->SetBranchAddress("y_tg_rec",     &y_tg_rec);
	aTree->SetBranchAddress("th_tg_rec",    &th_tg_rec);
	aTree->SetBranchAddress("ph_tg_rec",    &ph_tg_rec);
	aTree->SetBranchAddress("reactz_rec",   &reactz_rec);
	aTree->SetBranchAddress("Angle_rec",    &Angle_rec);//rad
	aTree->SetBranchAddress("E_s",          &E_s);//GeV
	aTree->SetBranchAddress("E_p",          &E_p);//GeV
	aTree->SetBranchAddress("Theta",          &Theta);//degree
	aTree->SetBranchAddress("Qsq",          &Qsq);
	aTree->SetBranchAddress("Xbj",          &Xbj);
	// aTree->SetBranchAddress("cs_Final",     &cs_Final);
	aTree->SetBranchAddress("IsPassed",     &aIsPassed);

    ////Get Average Cross Section at the Center Angle
	//Get_XS* aXS = new Get_XS();
	//aXS->Load_Table(aTarget.Data(),aKin.Data());

	Double_t kTheta = 0.0, aCS = 0.0, aCS_Center = 0.0, aSum = 0.0, aSum_Center=0.0;
	Int_t aCount = 0;
	
	/*Old Target Density{{{*/
   /* const double aVZ_Max = 0.1020, aVZ_Min = -0.1020;*/
	//const double aStep = (aVZ_Max-aVZ_Min)/51.;//0.004
	//double aVZ[52], aRho[52], aRho1[52],aRho2[52],aRho3[52];
	//for(int i=0;i<52;i++){
		//aVZ[i] = 0.0; aRho[i] = 1.0; aRho2[i] = 1.0; aRho3[i] = 1.0;
	//}
	//double aRho_Sum = 0;
	//TString aDummy="X";

	//if(aTarget=="H2"||aTarget=="He3"||aTarget=="He4"){
		////TString aDensity_Profile = Form("/work/halla/e08014/disk1/yez/Xbj_Cross_Section/Target/%s_Profile.rho",aTarget.Data());
		////cerr<<Form("\t Reading Density Profile for %s from %s",aTarget.Data(), aDensity_Profile.Data())<<endl;
		////ifstream density(aDensity_Profile.Data()); 
		////density >> aDummy >> aDummy >> aDummy >> aDummy >> aDummy;
		////for(int i=0;i<52;i++){
			////density >> aVZ[i] >> aRho[i] >> aRho1[i] >> aRho2[i] >> aRho3[i];
			////aRho_Sum += aRho3[i];
		////}
		////density.close();
		//aRho_Sum /=52;
	//}
	//else
		/*aRho_Sum = 1.0;*/
	/*}}}*/
    
    /*Target Density{{{*/
    //const Int_t aBin_Rho = 52;
    //const double aVZ_Max = 0.1020, aVZ_Min = -0.1020;
    //const double aStep = (aVZ_Max-aVZ_Min)/51.;//0.004

    const Int_t aBin_Rho = 200;
    const double aVZ_Max = 0.095, aVZ_Min = -0.095;
    const double aStep = (aVZ_Max-aVZ_Min)/(aBin_Rho-1);//0.001

    double aVZ[aBin_Rho], aRho[aBin_Rho], aRho1[aBin_Rho],aRho2[aBin_Rho],aRho3[aBin_Rho];
    for(int i=0;i<aBin_Rho;i++){
        aVZ[i] = 0.0; aRho[i] = 1.0; aRho2[i] = 1.0; aRho3[i] = 1.0;
    }
    double aRho_Sum = 0;
    TString aDummy="X";

    if(aTarget=="H2"||aTarget=="He3"||aTarget=="He4"){
        TString aDensity_Profile = Form("/work/halla/e08014/disk1/yez/Xbj_Cross_Section/Target/%s_new.rho",aTarget.Data());
        cerr<<Form("\t Reading Density Profile for %s from %s",aTarget.Data(), aDensity_Profile.Data())<<endl;
        ifstream density(aDensity_Profile.Data()); 
        density >> aDummy >> aDummy >> aDummy >> aDummy >> aDummy;
        Double_t aY0, aY0_Err, aBF, aBF_Err;
        for(int i=0;i<aBin_Rho;i++){
            density >> aVZ[i] >> aY0 >> aY0_Err >> aBF >> aBF_Err;
            aVZ[i] /= 100.; //cm to m
            aRho3[i] = aY0 * (1+aBF * aI_avg);
            aRho_Sum += aRho3[i];
        }
        density.close();
        aRho_Sum /=aBin_Rho;
    }
    /*}}}*/
    
	/*Ep Bining{{{*/
	int aVZ_Bin = 0; double aWeight = 0.0;
	if(aBin_Variable=="Ep"){
		cerr<<"      --- Calculating SAMC Events in Ep binning"<<endl;
		for(int i=0;i<aNevt;i++){
			aTree->GetEntry(i);  
			//Put the real P0 and Angle values from the real data
				double E_p_new = aP0 * (1+dp_rec);
				double aSinA = sin(aAngle*TMath::DegToRad());
				double aCosA = cos(aAngle*TMath::DegToRad());
				double Angle_new = acos( (aCosA-ph_tg_rec*aSinA)/sqrt(1.+pow(th_tg_rec,2)+pow(ph_tg_rec,2))); 
			if(fabs(x_fp)       < aAccCut[0] &&
					fabs(y_fp)       < aAccCut[1] &&
					fabs(th_fp)      < aAccCut[2] &&
					fabs(ph_fp)      < aAccCut[3] &&
					fabs(dp_rec)     < aAccCut[4] &&
					fabs(y_tg_rec)   < aAccCut[5] &&
					fabs(th_tg_rec)  < aAccCut[6] &&
					fabs(ph_tg_rec)  < aAccCut[7] &&
					fabs(reactz_rec) < aAccCut[8] &&
					fabs(E_p_new - aBin)< aBinCut &&
					reactz_rec >= aVZ_Cut[0] &&
					reactz_rec < aVZ_Cut[1] &&
					//fabs(E_p - aBin)< aBinCut &&
					aIsPassed==1 ){

				//kTheta =  Angle_rec / TMath::DegToRad(); 
				kTheta =  Angle_new / TMath::DegToRad(); 
				aCS = aXS->gGet_XS(E_s,E_p_new,kTheta, 0);//0->rad, 1->Born, 2->DIS, 3->QE
				aCS_Center = aXS->gGet_XS(E_s,aBin,kTheta, 0);//0->rad, 1->Born, 2->DIS, 3->QE

				if(aTarget=="H2"||aTarget=="He3"||aTarget=="He4"){
					aVZ_Bin = (reactz_rec-aVZ_Min)/aStep;
					aWeight = aRho3[aVZ_Bin]/aRho_Sum; 
				}
				else
					aWeight = 1.0;

				if(aCS>1e-33){
					aCount++;
					aSum += aCS*aWeight;
				}
				if(!(aCount%1000))
					cerr<<Form(" --- Reading SAMC Event = %d, XS = %e", aCount, aCS)<<endl;
				if(aCS_Center>1e-33)
					aSum_Center += aCS_Center*aWeight;
			}
		}
		//Bin Center Correction from XS(Ep_Bin, Theta_Avg) to XS(Ep_Bin, Theta_Center) -- Z. Ye, 03/04/2012
		aBinCor[0] = aXS->gGet_XS_Center(aBin)/(aSum/aCount)*aWeight; 
	}
    /*End of Ep Bining}}}*/
    
    /*Xbj Bining{{{*/
	else if(aBin_Variable=="xbj"){
	    Double_t aSinSQ = 0.0, aEp_Bin = 0.0;
		for(int i=0;i<aNevt;i++){
			aTree->GetEntry(i);  
			//Put the real P0 and Angle values from the real data
			double E_p_new = aP0 * (1+dp_rec);
			double aSinA = sin(aAngle*TMath::DegToRad());
			double aCosA = cos(aAngle*TMath::DegToRad());
			double Angle_new = acos( (aCosA-ph_tg_rec*aSinA)/sqrt(1.+pow(th_tg_rec,2)+pow(ph_tg_rec,2))); 
			double Q2_new = 4.0*E_s*E_p_new*pow( sin(Angle_new/2.), 2);
			double xbj_new = Q2_new/2./TARGET_MASS_A/(E_s-E_p_new);

			if(fabs(x_fp)       < aAccCut[0] &&
					fabs(y_fp)       < aAccCut[1] &&
					fabs(th_fp)      < aAccCut[2] &&
					fabs(ph_fp)      < aAccCut[3] &&
					fabs(dp_rec)     < aAccCut[4] &&
					fabs(y_tg_rec)   < aAccCut[5] &&
					fabs(th_tg_rec)  < aAccCut[6] &&
					fabs(ph_tg_rec)  < aAccCut[7] &&
					fabs(reactz_rec) < aAccCut[8] &&
					fabs(xbj_new - aBin)< aBinCut &&
					//fabs(Xbj - aBin)< aBinCut &&
					aIsPassed==1 ){

                if(aTarget=="H2"||aTarget=="He3"||aTarget=="He4"){
                    aVZ_Bin = (reactz_rec-aVZ_Min)/aStep;
                    aWeight = aRho3[aVZ_Bin]/aRho_Sum; 
                }else
                    aWeight = 1.0;

				aSinSQ = pow(sin(Angle_new/2.0),2); //Define Sin(Theta/2.)^2
				aEp_Bin = E_s/(1.0+4.0*E_s*aSinSQ/(2.0*TARGET_MASS_A*aBin)); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 

				//kTheta =  Angle_rec / TMath::DegToRad(); 
				kTheta =  Angle_new / TMath::DegToRad(); 
				aCS = aXS->gGet_XS(E_s,E_p_new,kTheta, 0);//0->rad, 1->Born, 2->DIS, 3->QE
				aCS_Center = aXS->gGet_XS(E_s,aEp_Bin,kTheta, 0);//0->rad, 1->Born, 2->DIS, 3->QE
				
				if(aCS>1e-33){
					aSum += aCS*aWeight;
					aCount++;
				}
				if(!(aCount%1000))
					cerr<<Form(" --- Reading SAMC Event = %d, XS = %e", aCount, aCS)<<endl;
				if(aCS_Center>1e-33)
					aSum_Center += aCS_Center*aWeight;
			}
		}
		Double_t aTheta0 = 0.0;
		/*Get Theta0{{{*/
		if(aKin.Contains("3.1")||aKin.Contains("3.2"))
			aTheta0 = 21.0;
		else if(aKin.Contains("4.1")||aKin.Contains("4.2"))
			aTheta0 = 23.0;
		else if(aKin.Contains("5.0")||aKin.Contains("5.1")||aKin.Contains("5.05")||aKin.Contains("5.2"))
			aTheta0 = 25.0;
		else if(aKin.Contains("6.5"))
			aTheta0 = 28.0;
		else 
			cerr<<"***ERROR***, in XGT2_SAMC.h, ln189, unknown Kinematic Setting!"<<endl;
		/*}}}*/
		aTheta0 = aAngle;//Use the real data scattering angle

		aSinSQ = pow(sin(aTheta0*TMath::DegToRad()/2.0),2); //Define Sin(Theta/2.)^2
        aEp_Bin = E_s/(1.0+4.0*E_s*aSinSQ/(2.0*TARGET_MASS_A*aBin)); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 

		//Bin Center Correction from XS(Ep_Bin, Theta_Avg) to XS(Ep_Bin, Theta_Center) -- Z. Ye, 03/04/2012
		aBinCor[0] = aXS->gGet_XS_Center(aEp_Bin)/(aSum/aCount); 
	}
	else{
		outlog <<"      *** ERROR, I am not able to calculate the SAMC SUM" <<endl;
		cerr   <<"      *** ERROR, I am not able to calculate the SAMC SUM" <<endl;
	}
    /*End of Xbj Bining}}}*/

	outlog <<"      SAMC XS Sum in this bin = " << aSum <<endl;
	cerr   <<"      SAMC XS Sum in this bin = " << aSum <<endl;

	sum->Value = aSum;
	if(aCount>0)//Swape Stat Err and Sys Err, Z. Ye 06/12/2014
		sum->Sys_Err = aSum * 1.0 / sqrt(aCount);
	else
		sum->Sys_Err = 0.0;
	sum->Stat_Err = 0.0;

	//delete aXS;
	return sum ; 
}
/*}}}*/

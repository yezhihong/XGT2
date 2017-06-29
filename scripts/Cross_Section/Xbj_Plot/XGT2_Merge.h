
/*gGet_Xbj_Cut{{{*/
void gGet_Xbj_Cut(const TString &aKinName, const TString & aArm, double* aXbj_Min, double* aXbj_Max){

	if(aKinName.Contains("Kin3.1")){
		if(aArm=="L"){
			aXbj_Min[0] = Xbj_Cut_21_1[0];		
			aXbj_Max[0] = Xbj_Cut_21_1[1];		
		}
		else if(aArm=="R"){
			aXbj_Min[0] = Xbj_Cut_21_1[2];		
			aXbj_Max[0] = Xbj_Cut_21_1[3];		
		}
	}
	else if(aKinName.Contains("Kin3.2")){
		if(aArm=="L"){
			aXbj_Min[0] = Xbj_Cut_21_2[0];		
			aXbj_Max[0] = Xbj_Cut_21_2[1];		
		}
		else if(aArm=="R"){
			aXbj_Min[0] = Xbj_Cut_21_2[2];		
			aXbj_Max[0] = Xbj_Cut_21_2[3];		
		}
	}

	else if(aKinName.Contains("Kin4.1")){
		if(aArm=="L"){
			aXbj_Min[0] = Xbj_Cut_23_1[0];		
			aXbj_Max[0] = Xbj_Cut_23_1[1];		
		}
		else if(aArm=="R"){
			aXbj_Min[0] = Xbj_Cut_23_1[2];		
			aXbj_Max[0] = Xbj_Cut_23_1[3];		
		}
	}
	else if(aKinName.Contains("Kin4.2")){
		if(aArm=="L"){
			aXbj_Min[0] = Xbj_Cut_23_2[0];		
			aXbj_Max[0] = Xbj_Cut_23_2[1];		
		}
		else if(aArm=="R"){
			aXbj_Min[0] = Xbj_Cut_23_2[2];		
			aXbj_Max[0] = Xbj_Cut_23_2[3];		
		}
	}

	else if(aKinName.Contains("Kin5.0") && ! aKinName.Contains("Kin5.05")){
		if(aArm=="L"){
			aXbj_Min[0] = Xbj_Cut_QE_1[0];		
			aXbj_Max[0] = Xbj_Cut_QE_1[1];		
		}
		else if(aArm=="R"){
			aXbj_Min[0] = Xbj_Cut_QE_1[2];		
			aXbj_Max[0] = Xbj_Cut_QE_1[3];		
		}
	}
	else if(aKinName.Contains("Kin5.05")){
		if(aArm=="L"){
			aXbj_Min[0] = Xbj_Cut_QE_2[0];		
			aXbj_Max[0] = Xbj_Cut_QE_2[1];		
		}
		else if(aArm=="R"){
			aXbj_Min[0] = Xbj_Cut_QE_2[2];		
			aXbj_Max[0] = Xbj_Cut_QE_2[3];		
		}
	}

	else if(aKinName.Contains("Kin5.1")){
		if(aArm=="L"){
			aXbj_Min[0] = Xbj_Cut_25_1[0];		
			aXbj_Max[0] = Xbj_Cut_25_1[1];		
		}
		else if(aArm=="R"){
			aXbj_Min[0] = Xbj_Cut_25_1[2];		
			aXbj_Max[0] = Xbj_Cut_25_1[3];		
		}
	}
	else if(aKinName.Contains("Kin5.2")){
		if(aArm=="L"){
			aXbj_Min[0] = Xbj_Cut_25_2[0];		
			aXbj_Max[0] = Xbj_Cut_25_2[1];		
		}
		else if(aArm=="R"){
			aXbj_Min[0] = Xbj_Cut_25_2[2];		
			aXbj_Max[0] = Xbj_Cut_25_2[3];		
		}
	}

	else if(aKinName.Contains("Kin6.5")){
		if(aArm=="L"){
			aXbj_Min[0] = Xbj_Cut_28_1[0];		
			aXbj_Max[0] = Xbj_Cut_28_1[1];		
		}
		else if(aArm=="R"){
			aXbj_Min[0] = Xbj_Cut_28_1[2];		
			aXbj_Max[0] = Xbj_Cut_28_1[3];		
		}
	}

	else{
		aXbj_Min[0]=-1.0;
		aXbj_Max[0]=10.0;
	}

}
/*}}}*/

/*Merge{{{*//*{{{*/
void Merge(const TString& aInputFileName, double* aXbj, double* aR_EX, double* aR_EX_Err, double* aR_MC, int* aN){

	/*Pre-define{{{*/	
	int aline = 0;
	TString aInputFilePath = "/work/halla/e08014/disk1/yez/Xbj_Cross_Section/results/";

	double scale = 1.0;
	double scale_mc = 1.0;
	//First Target:
	const TString aName_T1L1 = gGet_InputFile_Var(aInputFileName, aline); aline++;
	const TString aName_T1L2 = gGet_InputFile_Var(aInputFileName, aline); aline++;
	const TString aName_T1R1 = gGet_InputFile_Var(aInputFileName, aline); aline++;
	const TString aName_T1R2 = gGet_InputFile_Var(aInputFileName, aline); aline++;
	//Second Target:
	const TString aName_T2L1 = gGet_InputFile_Var(aInputFileName, aline); aline++;
	const TString aName_T2L2 = gGet_InputFile_Var(aInputFileName, aline); aline++;
	const TString aName_T2R1 = gGet_InputFile_Var(aInputFileName, aline); aline++;
	const TString aName_T2R2 = gGet_InputFile_Var(aInputFileName, aline); aline++;
	const double factor = gGet_InputFile_Var(aInputFileName, aline).Atof(); 
        factor00 = factor;

	double Theta = 21.00;
	TString Target = "C12";
	TString Kin = "3.1";
	double Xbj_Min = 1000.0, Xbj_Max = -1000.0;
	Double_t nu,Q2,xbj,angle,Ep,Livetime,LT_Syst_Err,Ntg,Ntg_Syst_Err,Ni,Ni_Syst_Err,Nf_EX,Nf_SAMC,Nf_SAMC_Gen,BinCor;
	Double_t XS,XS_Stat_Err,XS_Syst_Err,XS_MC,Yield_MC,Yield_EX,Y_MC_Syst_Err,Y_EX_Syst_Err,Y_MC_Stat_Err,Y_EX_Stat_Err;
	Double_t Nf_AL, Yield_AL, Y_AL_Stat_Err, Y_AL_Syst_Err;
	TString comment;
	Double_t aRadCorr = 0.0;
	/*}}}*/

	/*First Target{{{*/
	cerr<<endl<<"------------------- First Target ----------------------------------------------------------"<<endl<<endl;

	/*Define{{{*/
	Double_t XS_T1L1[200], XS_StatErr_T1L1[200], XS_SystErr_T1L1[200], Ep_T1L1[200], Xbj_T1L1[200],  XS_MC_T1L1[200];
	Double_t XS_T1L2[200], XS_StatErr_T1L2[200], XS_SystErr_T1L2[200], Ep_T1L2[200], Xbj_T1L2[200],  XS_MC_T1L2[200];
	Double_t XS_T1R1[200], XS_StatErr_T1R1[200], XS_SystErr_T1R1[200], Ep_T1R1[200], Xbj_T1R1[200],  XS_MC_T1R1[200];
	Double_t XS_T1R2[200], XS_StatErr_T1R2[200], XS_SystErr_T1R2[200], Ep_T1R2[200], Xbj_T1R2[200],  XS_MC_T1R2[200];
	/*}}}*/

	/*First{{{*/
	Target = gGet_Target_Name(aName_T1L1.Data());
	TString Target1 = Target;

	TString infile_T1L1 = aInputFilePath +Target+"/"+Com0+"/"+ aName_T1L1 +"_"+ Com0;
	cerr<<"==== Reading 1st file from "<<infile_T1L1<<endl;
	ifstream run_T1L1; run_T1L1.open(infile_T1L1);

	int Count_T1L1 =0;
        if(Target1=="He4"){
            scale = He4_Norm;
            scale_mc = He4_MC_Norm;
        }
        else if(Target1=="He3"){
            scale = He3_Norm;
            scale_mc = He3_MC_Norm;
        }

        else{
            scale = 1.0;
            scale_mc = 1.0;
        }

	Kin = gGet_Kin_Name(infile_T1L1.Data());

	if(Kin=="MM"){
		cerr<<"1st: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
	}
	if(Kin=="3.1"||Kin=="3.2")
		Theta = 21.00; 
	else if(Kin=="4.1"||Kin=="4.2")
		Theta = 23.00;
	else if(Kin=="5.0"||Kin=="5.05"||Kin=="5.1"||Kin=="5.2")
		Theta =  25.00;
	else if(Kin=="6.5")
		Theta = 28.00;
	else
		cerr<<"*** ERROR, unknown kinematics setting!"<<endl;

	TString Kin0 = Kin;
	TString Arm_T1L1="X";
	if(aName_T1L1.Contains("L_"))
		Arm_T1L1="L";
	else if(aName_T1L1.Contains("R_"))
		Arm_T1L1="R";

	TString KinName_T1L1 = Form("Kin%s",Kin.Data());
	gGet_Xbj_Cut(KinName_T1L1.Data(), Arm_T1L1.Data(),&Xbj_Min, &Xbj_Max);
	cerr<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T1L1.Data(), Xbj_Min,Xbj_Max)<<endl;

	Get_XS* xs_T1L1 = new Get_XS();
	xs_T1L1->Load_Table(Target.Data(),KinName_T1L1.Data());
	
        ofstream out_err(Form("./%s/err_%s_%s_%s_%s_%s.dat",OutFile_Dir.Data(), Kin0.Data(),Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));

	double T1L1_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T1L1.Data(),Theta);
	comment.ReadLine(run_T1L1);
	while ( run_T1L1>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
	{
		if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5&&xbj<=3.50 && XS>0.0 && sqrt(pow(XS_Syst_Err,2)+pow(XS_Stat_Err,2))/XS <0.5)
		{
			Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2);
			Ep_T1L1[Count_T1L1] = Ep; 
			XS_T1L1[Count_T1L1] = XS * scale; 
			XS_StatErr_T1L1[Count_T1L1] = XS_Stat_Err;
			XS_SystErr_T1L1[Count_T1L1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2));
			//XS_SystErr_T1L1[Count_T1L1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2)+pow(Ntg_Syst_Err/Ntg,2));
			Xbj_T1L1[Count_T1L1] = xbj;    
			XS_MC_T1L1[Count_T1L1] = xs_T1L1->gGet_XS_Born(E0,Ep,Theta) * scale_mc;

			cerr<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%e, XS_MC=%e",Target.Data(),
					KinName_T1L1.Data(), Ep_T1L1[Count_T1L1], Xbj_T1L1[Count_T1L1], 
					XS_T1L1[Count_T1L1],XS_MC_T1L1[Count_T1L1])<<endl;

                        out_err <<Form( "T1L1  %6.4f  %6.4f  %6.4f", xbj,LT_Syst_Err/Livetime, Ni_Syst_Err/Ni)<<endl;
                        Count_T1L1++;
		}
		if ( !run_T1L1.good() )
			break;
	}
	run_T1L1.close();
	delete xs_T1L1;
	cerr << "  Total XS Points for 1st = " << Count_T1L1 <<endl;
	/*}}}*/

	/*Second{{{*/
	TString KinName_T1L2 ="";
	Bool_t bMore_T1L2 = kTRUE;
	TString infile_T1L2 = aInputFilePath +Target+"/"+Com0+"/"+  aName_T1L2 +"_"+ Com0;
	cerr<<"==== Reading 2nd file from "<<infile_T1L2<<endl;
	TString Arm_T1L2="X";
	if(aName_T1L2 =="0")
		bMore_T1L2 = kFALSE;
	if(aName_T1L2.Contains("L_"))
		Arm_T1L2="L";
	else if(aName_T1L2.Contains("R_"))
		Arm_T1L2="R";

	double T1L2_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T1L2.Data(),Theta);
	int Count_T1L2=0;
	if(bMore_T1L2){
		ifstream run_T1L2; run_T1L2.open(infile_T1L2);
                Target = gGet_Target_Name(infile_T1L2.Data());
                if(Target1=="He3"){
                    scale = He3_Norm;
                    scale_mc = He3_MC_Norm;
                }
                else if(Target1=="He4"){
                    scale = He4_Norm;
                    scale_mc = He4_MC_Norm;
                }
                else{
                    scale = 1.0;
                    scale_mc = 1.0;
                }


		Kin = gGet_Kin_Name(infile_T1L2.Data());
		if(Kin=="MM"){
			cerr<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
		}
		if(Kin=="3.1"||Kin=="3.2")
			Theta = 21.00;
		else if(Kin=="4.1"||Kin=="4.2")
			Theta = 23.00;
		else if(Kin=="5.0"||Kin=="5.05"||Kin=="5.1"||Kin=="5.2")
			Theta =  25.00;
		else if(Kin=="6.5")
			Theta = 28.00;
		else
			cerr<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T1L2 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T1L2.Data(), Arm_T1L2.Data(),&Xbj_Min, &Xbj_Max);
		cerr<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T1L2.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T1L2 = new Get_XS();
		xs_T1L2->Load_Table(Target.Data(),KinName_T1L2.Data());

		comment.ReadLine(run_T1L2);
		while ( run_T1L2>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5 &&xbj<=3.50  && XS>0.0 && sqrt(pow(XS_Syst_Err,2)+pow(XS_Stat_Err,2))/XS <0.5)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2);
				Ep_T1L2[Count_T1L2] = Ep; 
				XS_T1L2[Count_T1L2] = XS * scale;    
				XS_StatErr_T1L2[Count_T1L2] = XS_Stat_Err;
				XS_SystErr_T1L2[Count_T1L2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2));
				//XS_SystErr_T1L2[Count_T1L2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2)+pow(Ntg_Syst_Err/Ntg,2));
				Xbj_T1L2[Count_T1L2] = xbj;    
				XS_MC_T1L2[Count_T1L2] = xs_T1L2->gGet_XS_Born(E0,Ep,Theta)*scale_mc;

				cerr<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%e, XS_MC=%e",Target.Data(),
						KinName_T1L2.Data(), Ep_T1L2[Count_T1L2], Xbj_T1L2[Count_T1L2], 
						XS_T1L2[Count_T1L2],XS_MC_T1L2[Count_T1L2])<<endl;

				Count_T1L2++;
                                out_err <<Form( "T1L2  %6.4f  %6.4f  %6.4f", xbj,LT_Syst_Err/Livetime, Ni_Syst_Err/Ni)<<endl;
                        }
			if ( !run_T1L2.good() )
				break;
		}
		run_T1L2.close();
		delete xs_T1L2;
		cerr << "  Total XS Points for 2nd  = " << Count_T1L2 <<endl;
	}
	/*}}}*/

	/*Third{{{*/
	TString KinName_T1R1 ="";
	Bool_t bMore_T1R1 = kTRUE;
	TString infile_T1R1 =  aInputFilePath +Target+"/"+Com0+"/"+ aName_T1R1 +"_"+ Com0;
	cerr<<"==== Reading 3rd file from "<<infile_T1R1<<endl;
	TString Arm_T1R1="X";
	if(aName_T1R1 =="0")
		bMore_T1R1 = kFALSE;
	if(aName_T1R1.Contains("L_"))
		Arm_T1R1="L";
	else if(aName_T1R1.Contains("R_"))
		Arm_T1R1="R";

	double T1R1_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T1R1.Data(),Theta);
	int Count_T1R1=0;
	if(bMore_T1R1){
		ifstream run_T1R1; run_T1R1.open(infile_T1R1);
		Target = gGet_Target_Name(infile_T1R1.Data());
        if(Target1=="He3"){
            scale = He3_Norm;
            scale_mc = He3_MC_Norm;
        }  
        else if(Target1=="He4"){
            scale = He4_Norm;
            scale_mc = He4_MC_Norm;
        }
        else{
            scale = 1.0;
            scale_mc = 1.0;
        }


		Kin = gGet_Kin_Name(infile_T1R1.Data());
		if(Kin=="MM"){
			cerr<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
		}
		if(Kin=="3.1"||Kin=="3.2")
			Theta = 21.00;
		else if(Kin=="4.1"||Kin=="4.2")
			Theta = 23.00;
		else if(Kin=="5.0"||Kin=="5.05"||Kin=="5.1"||Kin=="5.2")
			Theta =  25.00;
		else if(Kin=="6.5")
			Theta = 28.00;
		else
			cerr<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T1R1 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T1R1.Data(), Arm_T1R1.Data(),&Xbj_Min, &Xbj_Max);
		cerr<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T1R1.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T1R1 = new Get_XS();
		xs_T1R1->Load_Table(Target.Data(),KinName_T1R1.Data());

		comment.ReadLine(run_T1R1);
		while ( run_T1R1>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5 &&xbj<=3.50  && XS>0.0 && sqrt(pow(XS_Syst_Err,2)+pow(XS_Stat_Err,2))/XS <0.5)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2);
				Ep_T1R1[Count_T1R1] = Ep; 
				XS_T1R1[Count_T1R1] = XS * scale; 
				XS_StatErr_T1R1[Count_T1R1] = XS_Stat_Err;
				XS_SystErr_T1R1[Count_T1R1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2));
				//XS_SystErr_T1R1[Count_T1R1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2)+pow(Ntg_Syst_Err/Ntg,2));
				Xbj_T1R1[Count_T1R1] = xbj;    
				XS_MC_T1R1[Count_T1R1] = xs_T1R1->gGet_XS_Born(E0,Ep,Theta)*scale_mc;

				cerr<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%e, XS_MC=%e",Target.Data(),
						KinName_T1R1.Data(), Ep_T1R1[Count_T1R1], Xbj_T1R1[Count_T1R1], 
						XS_T1R1[Count_T1R1],XS_MC_T1R1[Count_T1R1])<<endl;

				Count_T1R1++;
                                out_err <<Form( "T1R1  %6.4f  %6.4f  %6.4f", xbj,LT_Syst_Err/Livetime, Ni_Syst_Err/Ni)<<endl;
                        }
			if ( !run_T1R1.good() )
				break;
		}
		run_T1R1.close();
		delete xs_T1R1;
		cerr << "  Total XS Points for 2nd  = " << Count_T1R1 <<endl;
	}
	/*}}}*/

	/*Forth{{{*/
	TString KinName_T1R2 ="";
	Bool_t bMore_T1R2 = kTRUE;
	TString infile_T1R2 = aInputFilePath +Target+"/"+Com0+"/"+  aName_T1R2 +"_"+ Com0;
	cerr<<"==== Reading 4th file from "<<infile_T1R2<<endl;
	TString Arm_T1R2="X";
	if(aName_T1R2 =="0")
		bMore_T1R2 = kFALSE;
	if(aName_T1R2.Contains("L_"))
		Arm_T1R2="L";
	else if(aName_T1R2.Contains("R_"))
            Arm_T1R2="R";

        double T1R2_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T1R2.Data(),Theta);
        int Count_T1R2=0;
        if(bMore_T1R2){
            ifstream run_T1R2; run_T1R2.open(infile_T1R2);
            Target = gGet_Target_Name(infile_T1R2.Data());
            if(Target1=="He3"){
                scale = He3_Norm;
                scale_mc = He3_MC_Norm;
            }
            else if(Target1=="He4"){
                scale = He4_Norm;
                scale_mc = He4_MC_Norm;
            }
            else{
                scale = 1.0;
                scale_mc = 1.0;
            }

            Kin = gGet_Kin_Name(infile_T1R2.Data());
            if(Kin=="MM"){
                cerr<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
		}
		if(Kin=="3.1"||Kin=="3.2")
			Theta = 21.00;
		else if(Kin=="4.1"||Kin=="4.2")
			Theta = 23.00;
		else if(Kin=="5.0"||Kin=="5.05"||Kin=="5.1"||Kin=="5.2")
			Theta =  25.00;
		else if(Kin=="6.5")
			Theta = 28.00;
		else
			cerr<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T1R2 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T1R2.Data(), Arm_T1R2.Data(),&Xbj_Min, &Xbj_Max);
		cerr<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T1R2.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T1R2 = new Get_XS();
		xs_T1R2->Load_Table(Target.Data(),KinName_T1R2.Data());

		comment.ReadLine(run_T1R2);
		while ( run_T1R2>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5  &&xbj<=3.50 && XS>0.0 && sqrt(pow(XS_Syst_Err,2)+pow(XS_Stat_Err,2))/XS <0.5)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2);
				Ep_T1R2[Count_T1R2] = Ep; 
				XS_T1R2[Count_T1R2] = XS * scale;
				XS_StatErr_T1R2[Count_T1R2] = XS_Stat_Err;
				XS_SystErr_T1R2[Count_T1R2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2));
				//XS_SystErr_T1R2[Count_T1R2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2)+pow(Ntg_Syst_Err/Ntg,2));
				Xbj_T1R2[Count_T1R2] = xbj;    
				XS_MC_T1R2[Count_T1R2] = xs_T1R2->gGet_XS_Born(E0,Ep,Theta)*scale_mc;

				cerr<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%e, XS_MC=%e",Target.Data(),
						KinName_T1R2.Data(), Ep_T1R2[Count_T1R2], Xbj_T1R2[Count_T1R2], 
						XS_T1R2[Count_T1R2],XS_MC_T1R2[Count_T1R2])<<endl;

                                out_err <<Form( "T1R2  %6.4f  %6.4f  %6.4f", xbj,LT_Syst_Err/Livetime, Ni_Syst_Err/Ni)<<endl;
				Count_T1R2++;
			}
			if ( !run_T1R2.good() )
				break;
		}
		run_T1R2.close();
		delete xs_T1R2;
		cerr << "  Total XS Points for 2nd  = " << Count_T1R2 <<endl;
	}
	/*}}}*/

	/*Merge{{{*/
	/*Add First Two Input{{{*/
	Double_t Ep_T1L[200],Xbj_T1L[200], XS_T1L[200], XS_StatErr_T1L[200], XS_SystErr_T1L[200], XS_MC_T1L[200];
	Double_t XS_Sum_T1L = 0.0, XS_StatErr_Sum_T1L = 0.0, XS_SystErr_Sum_T1L = 0.0; Int_t fSum_T1L = 0;
	int Count_T1L = 0, J_T1L =-1;

        bool bFirst_T1L=kTRUE; int J0_T1L = -1;
	for(int i=0;i<Count_T1L1;i++){
		XS_Sum_T1L = XS_T1L1[i];
		XS_StatErr_Sum_T1L = 1./pow(XS_StatErr_T1L1[i]/XS_T1L1[i],2);//N1
		XS_SystErr_Sum_T1L = pow(XS_SystErr_T1L1[i]/XS_T1L1[i],2);
		fSum_T1L = 1;
		//if(bMore_T1L2){
		for(int j=0;j<Count_T1L2;j++){
			//Find the verlapping bin for two setting, such as Kin3.1 and Kin3.2
			if(abs(Xbj_T1L1[i]-Xbj_T1L2[j])< 0.0001){
				XS_Sum_T1L += XS_T1L2[j];
				XS_StatErr_Sum_T1L += 1./pow(XS_StatErr_T1L2[j]/XS_T1L2[j],2);//N1+N2
				XS_SystErr_Sum_T1L += pow(XS_SystErr_T1L2[j]/XS_T1L2[j],2);
				fSum_T1L++; J_T1L = j;
	
                                if(bFirst_T1L){
                                  bFirst_T1L = kFALSE;
                                  J0_T1L = j;
                                }
                                
                                break; //No two xbj bin within one setting
			}
		}
		//}
		Ep_T1L[i] = Ep_T1L1[i];
		Xbj_T1L[i] = Xbj_T1L1[i];
		XS_MC_T1L[i] = XS_MC_T1L1[i];
		XS_T1L[i] = XS_Sum_T1L / fSum_T1L;
		XS_StatErr_T1L[i] = XS_T1L[i] * 1./sqrt(XS_StatErr_Sum_T1L); //1/sqrt(N1+N2)
		XS_SystErr_T1L[i] = XS_T1L[i] * sqrt(XS_SystErr_Sum_T1L) / fSum_T1L; 
		Count_T1L++;
	}
        if(J0_T1L>=1){
            for(int k=0;k<J0_T1L;k++){
                Ep_T1L[Count_T1L] = Ep_T1L2[k];
                Xbj_T1L[Count_T1L] = Xbj_T1L2[k];
                XS_T1L[Count_T1L] = XS_T1L2[k];
                XS_StatErr_T1L[Count_T1L] = XS_StatErr_T1L2[k];
                XS_SystErr_T1L[Count_T1L] = XS_SystErr_T1L2[k];
                XS_MC_T1L[Count_T1L] = XS_MC_T1L2[k];
                Count_T1L++;	
            }
        }
        for(int k=J_T1L+1;k<Count_T1L2;k++){
		Ep_T1L[Count_T1L] = Ep_T1L2[k];
		Xbj_T1L[Count_T1L] = Xbj_T1L2[k];
		XS_T1L[Count_T1L] = XS_T1L2[k];
		XS_StatErr_T1L[Count_T1L] = XS_StatErr_T1L2[k];
		XS_SystErr_T1L[Count_T1L] = XS_SystErr_T1L2[k];
		XS_MC_T1L[Count_T1L] = XS_MC_T1L2[k];
		Count_T1L++;	
	}


	/*}}}*/
	/*Add Last Two Input{{{*/
	Double_t Ep_T1R[200],Xbj_T1R[200], XS_T1R[200], XS_StatErr_T1R[200], XS_SystErr_T1R[200], XS_MC_T1R[200];
	Double_t XS_Sum_T1R = 0.0, XS_StatErr_Sum_T1R = 0.0, XS_SystErr_Sum_T1R = 0.0; Int_t fSum_T1R = 0;
	int Count_T1R = 0, J_T1R =-1;
        bool bFirst_T1R = kTRUE; int J0_T1R = -1;
	//if(bMore_T1R1){
	for(int i=0;i<Count_T1R1;i++){
		XS_Sum_T1R = XS_T1R1[i];
		XS_StatErr_Sum_T1R = 1./pow(XS_StatErr_T1R1[i]/XS_T1R1[i],2);//N1
		XS_SystErr_Sum_T1R = pow(XS_SystErr_T1R1[i]/XS_T1R1[i],2);
		fSum_T1R = 1;
		//if(bMore_T1R2){
		for(int j=0;j<Count_T1R2;j++){
			//Find the verlapping bin for two setting, such as Kin3.1 and Kin3.2
			if(abs(Xbj_T1R1[i]-Xbj_T1R2[j])< 0.0001){
				XS_Sum_T1R += XS_T1R2[j];
				XS_StatErr_Sum_T1R +=	1./pow(XS_StatErr_T1R2[j]/XS_T1R2[j],2);//N1+N2
				XS_SystErr_Sum_T1R +=	pow(XS_SystErr_T1R2[j]/XS_T1R2[j],2);
				fSum_T1R++; J_T1R = j;

                                if(bFirst_T1R){
                                   bFirst_T1R = kFALSE;
                                   J0_T1R = j;
                                }

				break; //No two xbj bin within one setting
			}
		}
		//}
		Ep_T1R[i] = Ep_T1R1[i];
		Xbj_T1R[i] = Xbj_T1R1[i];
		XS_MC_T1R[i] = XS_MC_T1R1[i];
		XS_T1R[i] = XS_Sum_T1R / fSum_T1R;
		XS_StatErr_T1R[i] = XS_T1R[i] * 1./sqrt(XS_StatErr_Sum_T1R); //1/sqrt(N1+N2)
		XS_SystErr_T1R[i] = XS_T1R[i] * sqrt(XS_SystErr_Sum_T1R) / fSum_T1R; 
		Count_T1R++;
	}
        if(J0_T1R>=1){
            for(int k=0;k<J_T1R;k++){
                Ep_T1R[Count_T1R] = Ep_T1R2[k];
                Xbj_T1R[Count_T1R] = Xbj_T1R2[k];
                XS_T1R[Count_T1R] = XS_T1R2[k];
                XS_StatErr_T1R[Count_T1R] = XS_StatErr_T1R2[k];
                XS_SystErr_T1R[Count_T1R] = XS_SystErr_T1R2[k];
                XS_MC_T1L[Count_T1R] = XS_MC_T1R2[k];
                Count_T1R++;	
            }
        }
	for(int k=J_T1R+1;k<Count_T1R2;k++){
		Ep_T1R[Count_T1R] = Ep_T1R2[k];
		Xbj_T1R[Count_T1R] = Xbj_T1R2[k];
		XS_T1R[Count_T1R] = XS_T1R2[k];
		XS_StatErr_T1R[Count_T1R] = XS_StatErr_T1R2[k];
		XS_SystErr_T1R[Count_T1R] = XS_SystErr_T1R2[k];
		XS_MC_T1L[Count_T1R] = XS_MC_T1R2[k];
		Count_T1R++;	
	}
	//}
	/*}}}*/

	/*OLD-Add All{{{*/
	double T1_Syst_Err_Com = (T1L1_Syst_Err+T1L2_Syst_Err+T1R1_Syst_Err+T1R2_Syst_Err)/4.0;
	vector<double> vEp1,vXbj1, vXbj_Err1,vXS1, vXS_Err1, vXS_MC1;
	vector<double> vXS1_StatErr, vXS1_LTQEErr, vXS1_SystErr;
	double XS_MC_T1, XS_T1, XS_Err_T1;
	double X_Min1 = 100.0, X_Max1 = -100.0, Y_Min1 = 10000.0, Y_Max1 = -10000.0;
	int N1 = 0, J1R= 0;
	bool bFound_T1L = kFALSE;
	if(Count_T1L>0&&Count_T1R>0){
	for(int i=0;i<Count_T1L; i++){
	bFound_T1L = kFALSE;	
	for(int j=0;j<Count_T1R; j++){
	if( abs(Xbj_T1L[i] - Xbj_T1R[j])<0.0001 ){
	vEp1.push_back(Ep_T1L[i]);	
	vXbj1.push_back(Xbj_T1L[i]);	
	bFound_T1L = kTRUE;	
	vXbj_Err1.push_back(0.0);	
	XS_T1 = (XS_T1L[i]+XS_T1R[j])/2.0;
	XS_Err_T1 = 1.0/( 1.0/pow(XS_StatErr_T1L[i]/XS_T1L[i],2) + 1.0/pow(XS_StatErr_T1R[j]/XS_T1R[j],2) );
	XS_Err_T1 +=(pow(XS_SystErr_T1L[i]/XS_T1L[i],2) + pow(XS_SystErr_T1R[j]/XS_T1R[j],2) )/2.0;
	XS_Err_T1 += pow(T1_Syst_Err_Com,2);
	XS_Err_T1 = XS_T1 * sqrt(XS_Err_T1);

	//XS_MC_T1 = 	(XS_MC_T1L[i]+XS_MC_T1R[j])/2.0;
	XS_MC_T1 = 	XS_MC_T1L[i];

	vXS1_StatErr.push_back(1.0/sqrt( (1.0/pow(XS_StatErr_T1L[i]/XS_T1L[i],2) + 1.0/pow(XS_StatErr_T1R[j]/XS_T1R[j],2))) );
	vXS1_LTQEErr.push_back(sqrt( (pow(XS_SystErr_T1L[i]/XS_T1L[i],2) + pow(XS_SystErr_T1R[j]/XS_T1R[j],2))/2.0) );
	vXS1_SystErr.push_back(T1_Syst_Err_Com);

	vXS1.push_back(XS_T1);
	vXS_Err1.push_back(XS_Err_T1);
	vXS_MC1.push_back( XS_MC_T1 );
	N1++; J1R = j;
	if(Xbj_T1L[i] < X_Min1)
	X_Min1 = Xbj_T1L[i];
	if(Xbj_T1L[i] > X_Max1)
	X_Max1 = Xbj_T1L[i];
	if(XS_T1 < Y_Min1)
	Y_Min1 = XS_T1;
	if(XS_T1 > Y_Max1)
	Y_Max1 = XS_T1;
	if(XS_MC_T1 < Y_Min1)
	Y_Min1 = XS_MC_T1;
	if(XS_T1 > Y_Max1)
	Y_Max1 = XS_MC_T1;
	}
	}
	if(!bFound_T1L){
	vEp1.push_back(Ep_T1L[i]);	
	vXbj1.push_back(Xbj_T1L[i]);	
	vXbj_Err1.push_back(0.0);	
	XS_T1 = XS_T1L[i];
	XS_Err_T1 =  pow(XS_StatErr_T1L[i]/XS_T1L[i],2);
	XS_Err_T1 += pow(XS_SystErr_T1L[i]/XS_T1L[i],2);
	XS_Err_T1 += pow(T1_Syst_Err_Com,2);
	XS_Err_T1 = XS_T1 * sqrt(XS_Err_T1);

	XS_MC_T1 = 	XS_MC_T1L[i];

	vXS1_StatErr.push_back(XS_StatErr_T1L[i]/XS_T1L[i]);
	vXS1_LTQEErr.push_back(XS_SystErr_T1L[i]/XS_T1L[i]);
	vXS1_SystErr.push_back(T1_Syst_Err_Com);

	vXS1.push_back(XS_T1);
	vXS_Err1.push_back(XS_Err_T1);
	vXS_MC1.push_back( XS_MC_T1 );
	N1++;
	if(Xbj_T1L[i] < X_Min1)
	X_Min1 = Xbj_T1L[i];
	if(Xbj_T1L[i] > X_Max1)
	X_Max1 = Xbj_T1L[i];
	if(XS_T1 < Y_Min1)
	Y_Min1 = XS_T1;
	if(XS_T1 > Y_Max1)
	Y_Max1 = XS_T1;
	if(XS_MC_T1 < Y_Min1)
	Y_Min1 = XS_MC_T1;
	if(XS_T1 > Y_Max1)
	Y_Max1 = XS_MC_T1;
	}
	}

	for(int k =J1R+1; k<Count_T1R; k++){
		vEp1.push_back(Ep_T1R[k]);	
		vXbj1.push_back(Xbj_T1R[k]);	
		vXbj_Err1.push_back(0.0);	
		XS_T1 = XS_T1R[k];
		XS_Err_T1 =  pow(XS_StatErr_T1R[k]/XS_T1R[k],2);
		XS_Err_T1 += pow(XS_SystErr_T1R[k]/XS_T1R[k],2);
		XS_Err_T1 += pow(T1_Syst_Err_Com,2);
		XS_Err_T1 = XS_T1 * sqrt(XS_Err_T1);

		XS_MC_T1 = 	XS_MC_T1R[k];

		vXS1_StatErr.push_back(XS_StatErr_T1R[k]/XS_T1R[k]);
		vXS1_LTQEErr.push_back(XS_SystErr_T1R[k]/XS_T1R[k]);
		vXS1_SystErr.push_back(T1_Syst_Err_Com);

		vXS1.push_back(XS_T1);
		vXS_Err1.push_back(XS_Err_T1);
		vXS_MC1.push_back( XS_MC_T1 );
		N1++;
		if(Xbj_T1R[k] < X_Min1)
			X_Min1 = Xbj_T1R[k];
		if(Xbj_T1R[k] > X_Max1)
			X_Max1 = Xbj_T1R[k];
		if(XS_T1 < Y_Min1)
			Y_Min1 = XS_T1;
		if(XS_T1 > Y_Max1)
			Y_Max1 = XS_T1;
		if(XS_MC_T1 < Y_Min1)
			Y_Min1 = XS_MC_T1;
		if(XS_T1 > Y_Max1)
			Y_Max1 = XS_MC_T1;
	}
    }
	else{
		for(int i=0;i<Count_T1L; i++){
			vEp1.push_back(Ep_T1L[i]);	
			vXbj1.push_back(Xbj_T1L[i]);	
			vXbj_Err1.push_back(0.0);	
			XS_T1 = XS_T1L[i];
			XS_Err_T1 =  pow(XS_StatErr_T1L[i]/XS_T1L[i],2);
			XS_Err_T1 += pow(XS_SystErr_T1L[i]/XS_T1L[i],2);
			XS_Err_T1 += pow(T1_Syst_Err_Com,2);
			XS_Err_T1 = XS_T1 * sqrt(XS_Err_T1);

			XS_MC_T1 = 	XS_MC_T1L[i];

			vXS1_StatErr.push_back(XS_StatErr_T1L[i]/XS_T1L[i]);
			vXS1_LTQEErr.push_back(XS_SystErr_T1L[i]/XS_T1L[i]);
			vXS1_SystErr.push_back(T1_Syst_Err_Com);

			vXS1.push_back(XS_T1);
			vXS_Err1.push_back(XS_Err_T1);
			vXS_MC1.push_back( XS_MC_T1 );
			N1++;
			if(Xbj_T1L[i] < X_Min1)
				X_Min1 = Xbj_T1L[i];
			if(Xbj_T1L[i] > X_Max1)
				X_Max1 = Xbj_T1L[i];
			if(XS_T1 < Y_Min1)
				Y_Min1 = XS_T1;
			if(XS_T1 > Y_Max1)
				Y_Max1 = XS_T1;
			if(XS_MC_T1 < Y_Min1)
				Y_Min1 = XS_MC_T1;
			if(XS_T1 > Y_Max1)
				Y_Max1 = XS_MC_T1;
		}
	}
	/*}}}*/

	/*RadCorr for He3 at x>2.45{{{*/
		if(Target=="He3"){
			for(unsigned int i=0;i<vXbj1.size(); i++){
				if(vXbj1[i]>=2.45){	
					aRadCorr = gGet_RadCorr_He3(vXbj1[i]);
					vXS1[i]*=aRadCorr;
					vXS_Err1[i]*=aRadCorr;
				}
			}
		}
	/*}}}*/

	/*}}}*/

	/*Plot{{{*/
	TCanvas *c1 = new TCanvas("c1","c1",1200,800);
	gPad->SetLogy(1);
	TH2F* xs1 = new TH2F("xs1","",1000,0.7,3.2,1000,Y_Min1/2.,Y_Max1*2.0);
	xs1->SetStats(kFALSE);
	xs1->SetXTitle("x");
	xs1->GetXaxis()->CenterTitle(1);
	xs1->GetXaxis()->SetTitleFont(22);
	xs1->GetXaxis()->SetTitleSize(0.06);
	xs1->SetYTitle("#frac{d#sigma}{dE'd#Omega} (nb/MeV/sr)");
	xs1->GetYaxis()->CenterTitle(1);
	xs1->GetYaxis()->SetTitleFont(22);
	xs1->GetYaxis()->SetTitleSize(0.04);
	xs1->Draw(); 

	TGraphErrors *pl_x1 = new TGraphErrors(N1,&vXbj1[0],&vXS1[0],&vXbj_Err1[0],&vXS_Err1[0]);
	pl_x1-> SetMarkerColor(2);
	pl_x1-> SetMarkerSize(1.0);
	pl_x1-> SetMarkerStyle(22);
	pl_x1-> GetXaxis()->SetTitle("x");
	pl_x1-> GetYaxis()->SetTitle("#sigma");
	pl_x1->Draw("P");

	TGraphErrors *pl_x11 = new TGraphErrors(N1,&vXbj1[0],&vXS_MC1[0],&vXbj_Err1[0],&vXbj_Err1[0]);
	pl_x11-> SetMarkerColor(0);
	pl_x11-> SetMarkerSize(0.0);
	pl_x11-> SetLineColor(4);
	pl_x11-> SetLineWidth(2);
	pl_x11-> SetMarkerStyle(20);
	pl_x11-> GetXaxis()->SetTitle("x");
	pl_x11-> GetYaxis()->SetTitle("#sigma_{mc}");
	pl_x11->Draw("L");

	TLegend *l1 = new TLegend(0.65,0.57,0.90, 0.90,Form("%s Target",Target.Data()));
	l1->SetTextSize(0.03);
	l1->SetTextFont(22);
	l1->AddEntry(pl_x1,  Form("XS_{EX} at %3.1f^{#circ}",Theta),"p");
	pl_x1->Draw("P");
	l1->AddEntry(pl_x11, Form("XS_{MC} at %3.1f^{#circ}",Theta),"l");
	pl_x11->Draw("L");
	l1->Draw();

	if(aInputFileName.Contains("QE")){
		c1->Print(Form("./%s/XS_%s_%2.0f_QE_%s.png",OutFile_Dir.Data(),  Target.Data(), Theta,Com0.Data()));
		c1->Print(Form("./%s/XS_%s_%2.0f_QE_%s.pdf",OutFile_Dir.Data(),  Target.Data(), Theta,Com0.Data()));
	}
	else{
		c1->Print(Form("./%s/XS_%s_%2.0f_%s.png",OutFile_Dir.Data(),  Target.Data(), Theta,Com0.Data()));
		c1->Print(Form("./%s/XS_%s_%2.0f_%s.pdf",OutFile_Dir.Data(),  Target.Data(), Theta,Com0.Data()));
	}
	/*}}}*/
	/*}}}*/

	/*Second Target{{{*/
	cerr<<endl<<"------------------ Second Target ----------------------------------------------------------"<<endl<<endl;

	/*Define{{{*/
	Double_t XS_T2L1[200], XS_SystErr_T2L1[200], XS_StatErr_T2L1[200], Ep_T2L1[200], Xbj_T2L1[200],  XS_MC_T2L1[200];
	Double_t XS_T2L2[200], XS_SystErr_T2L2[200], XS_StatErr_T2L2[200], Ep_T2L2[200], Xbj_T2L2[200],  XS_MC_T2L2[200];
	Double_t XS_T2R1[200], XS_SystErr_T2R1[200], XS_StatErr_T2R1[200], Ep_T2R1[200], Xbj_T2R1[200],  XS_MC_T2R1[200];
	Double_t XS_T2R2[200], XS_SystErr_T2R2[200], XS_StatErr_T2R2[200], Ep_T2R2[200], Xbj_T2R2[200],  XS_MC_T2R2[200];
	/*}}}*/

	/*First{{{*/
	Target = gGet_Target_Name(aName_T2L1.Data());
	TString Target2 = Target;

	TString infile_T2L1 = aInputFilePath +Target+"/"+Com+"/"+  aName_T2L1 +"_"+ Com;
	cerr<<"==== Reading 1st file from "<<infile_T2L1<<endl;
	ifstream run_T2L1; run_T2L1.open(infile_T2L1);

        int Count_T2L1 =0;
        if(Target2=="He3"){
            scale = He3_Norm;
            scale_mc = He3_MC_Norm;
        }
        else if(Target2=="He4"){
            scale = He4_Norm;
            scale_mc = He4_MC_Norm;
        }
        else{
            scale = 1.0;
            scale_mc = 1.0;
        }

	Kin = gGet_Kin_Name(infile_T2L1.Data());

	TString Arm_T2L1="X";
	if(aName_T2L1.Contains("L_"))
		Arm_T2L1="L";
	else if(aName_T2L1.Contains("R_"))
		Arm_T2L1="R";


	if(Kin=="MM"){
		cerr<<"1st: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
	}
	if(Kin=="3.1"||Kin=="3.2")
		Theta = 21.00; 
	else if(Kin=="4.1"||Kin=="4.2")
		Theta = 23.00;
	else if(Kin=="5.0"||Kin=="5.05"||Kin=="5.1"||Kin=="5.2")
		Theta =  25.00;
	else if(Kin=="6.5")
		Theta = 28.00;
	else
		cerr<<"*** ERROR, unknown kinematics setting!"<<endl;

	TString KinName_T2L1 = Form("Kin%s",Kin.Data());
	gGet_Xbj_Cut(KinName_T2L1.Data(), Arm_T2L1.Data(),&Xbj_Min, &Xbj_Max);
	cerr<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T2L1.Data(), Xbj_Min,Xbj_Max)<<endl;

	Get_XS* xs_T2L1 = new Get_XS();
	xs_T2L1->Load_Table(Target.Data(),KinName_T2L1.Data());

	double T2L1_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T2L1.Data(),Theta);
	comment.ReadLine(run_T2L1);
	while ( run_T2L1>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
	{
		if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Syst_Err,2)+pow(XS_Stat_Err,2))/XS <0.5)
		{
			Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2);
			Ep_T2L1[Count_T2L1]=Ep;
			XS_T2L1[Count_T2L1] = XS * scale;
			XS_StatErr_T2L1[Count_T2L1] = XS_Stat_Err;
			XS_SystErr_T2L1[Count_T2L1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2));
			//XS_SystErr_T2L1[Count_T2L1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2)+pow(Ntg_Syst_Err/Ntg,2));
			Xbj_T2L1[Count_T2L1] = xbj;    
			XS_MC_T2L1[Count_T2L1] = xs_T2L1->gGet_XS_Born(E0,Ep,Theta)*scale_mc;

			cerr<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%e, XS_MC=%e",Target.Data(),
					KinName_T2L1.Data(), Ep_T2L1[Count_T2L1], Xbj_T2L1[Count_T2L1], 
					XS_T2L1[Count_T2L1],XS_MC_T2L1[Count_T2L1])<<endl;

                        out_err <<Form( "T2L1  %6.4f  %6.4f  %6.4f", xbj,LT_Syst_Err/Livetime, Ni_Syst_Err/Ni)<<endl;

			Count_T2L1++;
		}
		if ( !run_T2L1.good() )
			break;
	}
	run_T2L1.close();
	delete xs_T2L1;
	cerr << "  Total XS Points for 1st = " << Count_T2L1 <<endl;
	/*}}}*/

	/*Second{{{*/
	TString KinName_T2L2 ="";
	Bool_t bMore_T2L2 = kTRUE;
	TString infile_T2L2 = aInputFilePath +Target+"/"+Com+"/"+  aName_T2L2 +"_"+ Com;
	cerr<<"==== Reading 2nd file from "<<infile_T2L2<<endl;
	TString Arm_T2L2="X";
	if(aName_T2L2 =="0")
		bMore_T2L2 = kFALSE;
	if(aName_T2L2.Contains("L_"))
		Arm_T2L2="L";
	else if(aName_T2L2.Contains("R_"))
		Arm_T2L2="R";

	double T2L2_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T2L2.Data(),Theta);
	int Count_T2L2=0;
	if(bMore_T2L2){
		ifstream run_T2L2; run_T2L2.open(infile_T2L2);
		Target = gGet_Target_Name(infile_T2L2.Data());
        if(Target2=="He3"){
            scale = He3_Norm;
            scale_mc = He3_MC_Norm;
        }
        else if(Target2=="He4"){
            scale = He4_Norm;
            scale_mc = He4_MC_Norm;
        }
        else{
            scale = 1.0;
            scale_mc = 1.0;
        }

		Kin = gGet_Kin_Name(infile_T2L2.Data());
		if(Kin=="MM"){
			cerr<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
		}
		if(Kin=="3.1"||Kin=="3.2")
			Theta = 21.00;
		else if(Kin=="4.1"||Kin=="4.2")
			Theta = 23.00;
		else if(Kin=="5.0"||Kin=="5.05"||Kin=="5.1"||Kin=="5.2")
			Theta =  25.00;
		else if(Kin=="6.5")
			Theta = 28.00;
		else
			cerr<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T2L2 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T2L2.Data(), Arm_T2L2.Data(),&Xbj_Min, &Xbj_Max);
		cerr<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T2L2.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T2L2 = new Get_XS();
		xs_T2L2->Load_Table(Target.Data(),KinName_T2L2.Data());

		comment.ReadLine(run_T2L2);
		while ( run_T2L2>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Syst_Err,2)+pow(XS_Stat_Err,2))/XS <0.5)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2);
				Ep_T2L2[Count_T2L2]=Ep;
				XS_T2L2[Count_T2L2] = XS * scale; 
				XS_StatErr_T2L2[Count_T2L2] = XS_Stat_Err;
				XS_SystErr_T2L2[Count_T2L2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2));
				//XS_SystErr_T2L2[Count_T2L2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2)+pow(Ntg_Syst_Err/Ntg,2));
				Xbj_T2L2[Count_T2L2] = xbj;    
				XS_MC_T2L2[Count_T2L2] = xs_T2L2->gGet_XS_Born(E0,Ep,Theta)*scale_mc;

				cerr<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%e, XS_MC=%e",Target.Data(),
						KinName_T2L2.Data(), Ep_T2L2[Count_T2L2], Xbj_T2L2[Count_T2L2], 
						XS_T2L2[Count_T2L2],XS_MC_T2L2[Count_T2L2])<<endl;
                        
                                out_err <<Form( "T2L2  %6.4f  %6.4f  %6.4f", xbj,LT_Syst_Err/Livetime, Ni_Syst_Err/Ni)<<endl;

				Count_T2L2++;
			}
			if ( !run_T2L2.good() )
				break;
		}
		run_T2L2.close();
		delete xs_T2L2;
		cerr << "  Total XS Points for 2nd  = " << Count_T2L2 <<endl;
	}
	/*}}}*/

	/*Third{{{*/
	TString KinName_T2R1 ="";
	Bool_t bMore_T2R1 = kTRUE;
	TString infile_T2R1 = aInputFilePath +Target+"/"+Com+"/"+  aName_T2R1 +"_"+ Com;
	cerr<<"==== Reading 3rd file from "<<infile_T2R1<<endl;
	TString Arm_T2R1="X";
	if(aName_T2R1 =="0")
		bMore_T2R1 = kFALSE;
	if(aName_T2R1.Contains("L_"))
		Arm_T2R1="L";
	else if(aName_T2R1.Contains("R_"))
		Arm_T2R1="R";

	double T2R1_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T2R1.Data(),Theta);
	int Count_T2R1=0;
	if(bMore_T2R1){
            ifstream run_T2R1; run_T2R1.open(infile_T2R1);
            Target = gGet_Target_Name(infile_T2R1.Data());
            if(Target2=="He3"){
                scale = He3_Norm;
                scale_mc = He3_MC_Norm;
            }
            else if(Target2=="He4"){
                scale = He4_Norm;
                scale_mc = He4_MC_Norm;
            }
            else{
                scale = 1.0;
                scale_mc = 1.0;
            }


		Kin = gGet_Kin_Name(infile_T2R1.Data());
		if(Kin=="MM"){
			cerr<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
		}
		if(Kin=="3.1"||Kin=="3.2")
			Theta = 21.00;
		else if(Kin=="4.1"||Kin=="4.2")
			Theta = 23.00;
		else if(Kin=="5.0"||Kin=="5.05"||Kin=="5.1"||Kin=="5.2")
			Theta =  25.00;
		else if(Kin=="6.5")
			Theta = 28.00;
		else
			cerr<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T2R1 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T2R1.Data(), Arm_T2R1.Data(),&Xbj_Min, &Xbj_Max);
		cerr<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T2R1.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T2R1 = new Get_XS();
		xs_T2R1->Load_Table(Target.Data(),KinName_T2R1.Data());

		comment.ReadLine(run_T2R1);
		while ( run_T2R1>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Syst_Err,2)+pow(XS_Stat_Err,2))/XS <0.5)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2);
				Ep_T2R1[Count_T2R1]=Ep;
				XS_T2R1[Count_T2R1] = XS* scale;   
				XS_StatErr_T2R1[Count_T2R1] = XS_Stat_Err;
				XS_SystErr_T2R1[Count_T2R1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2));
				//XS_SystErr_T2R1[Count_T2R1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2)+pow(Ntg_Syst_Err/Ntg,2));
				Xbj_T2R1[Count_T2R1] = xbj;    
				XS_MC_T2R1[Count_T2R1] = xs_T2R1->gGet_XS_Born(E0,Ep,Theta)*scale_mc;

				cerr<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%e, XS_MC=%e",Target.Data(),
						KinName_T2R1.Data(), Ep_T2R1[Count_T2R1], Xbj_T2R1[Count_T2R1], 
						XS_T2R1[Count_T2R1],XS_MC_T2R1[Count_T2R1])<<endl;
                                
                                out_err <<Form( "T2R1  %6.4f  %6.4f  %6.4f", xbj,LT_Syst_Err/Livetime, Ni_Syst_Err/Ni)<<endl;

				Count_T2R1++;
			}
			if ( !run_T2R1.good() )
				break;
		}
		run_T2R1.close();
		delete xs_T2R1;
		cerr << "  Total XS Points for 2nd  = " << Count_T2R1 <<endl;
	}
	/*}}}*/

	/*Forth{{{*/
	TString KinName_T2R2 ="";
	Bool_t bMore_T2R2 = kTRUE;
	TString infile_T2R2 = aInputFilePath +Target+"/"+Com+"/"+ aName_T2R2 +"_"+ Com;
	cerr<<"==== Reading 4th file from "<<infile_T2R2<<endl;
	TString Arm_T2R2="X";
	if(aName_T2R2 =="0")
		bMore_T2R2 = kFALSE;
	if(aName_T2R2.Contains("L_"))
		Arm_T2R2="L";
	else if(aName_T2R2.Contains("R_"))
		Arm_T2R2="R";

	double T2R2_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T2R2.Data(),Theta);
	int Count_T2R2=0;
	if(bMore_T2R2){
		ifstream run_T2R2; run_T2R2.open(infile_T2R2);
		Target = gGet_Target_Name(infile_T2R2.Data());
                if(Target2=="He3"){
                    scale = He3_Norm;
                    scale_mc = He3_MC_Norm;
                }
                else if(Target2=="He4"){
                    scale = He4_Norm;
                    scale_mc = He4_MC_Norm;
                }
                else{
                    scale = 1.0;
                    scale_mc = 1.0;
                }


		Kin = gGet_Kin_Name(infile_T2R2.Data());
		if(Kin=="MM"){
			cerr<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
		}
		if(Kin=="3.1"||Kin=="3.2")
			Theta = 21.00;
		else if(Kin=="4.1"||Kin=="4.2")
			Theta = 23.00;
		else if(Kin=="5.0"||Kin=="5.05"||Kin=="5.1"||Kin=="5.2")
			Theta =  25.00;
		else if(Kin=="6.5")
			Theta = 28.00;
		else
			cerr<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T2R2 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T2R2.Data(), Arm_T2R2.Data(),&Xbj_Min, &Xbj_Max);
		cerr<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T2R2.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T2R2 = new Get_XS();
		xs_T2R2->Load_Table(Target.Data(),KinName_T2R2.Data());

		comment.ReadLine(run_T2R2);
		while ( run_T2R2>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Syst_Err,2)+pow(XS_Stat_Err,2))/XS <0.5)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2);
				Ep_T2R2[Count_T2R2]=Ep;
				XS_T2R2[Count_T2R2] = XS * scale;     
				XS_StatErr_T2R2[Count_T2R2] = XS_Stat_Err;
				XS_SystErr_T2R2[Count_T2R2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2));
				//XS_SystErr_T2R2[Count_T2R2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2)+pow(Ni_Syst_Err/Ni,2)+pow(Ntg_Syst_Err/Ntg,2));
				Xbj_T2R2[Count_T2R2] = xbj;    
				XS_MC_T2R2[Count_T2R2] = xs_T2R2->gGet_XS_Born(E0,Ep,Theta)*scale_mc;

				cerr<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%e, XS_MC=%e",Target.Data(),
						KinName_T2R2.Data(), Ep_T2R2[Count_T2R2], Xbj_T2R2[Count_T2R2], 
						XS_T2R2[Count_T2R2],XS_MC_T2R2[Count_T2R2])<<endl;

                                out_err <<Form( "T2R2  %6.4f  %6.4f  %6.4f", xbj,LT_Syst_Err/Livetime, Ni_Syst_Err/Ni)<<endl;
				Count_T2R2++;
			}
			if ( !run_T2R2.good() )
				break;
		}
		run_T2R2.close();
		delete xs_T2R2;
		cerr << "  Total XS Points for 2nd  = " << Count_T2R2 <<endl;
	}
	/*}}}*/

	/*Merge{{{*/
	/*Add First Two Input{{{*/
	Double_t Ep_T2L[200],Xbj_T2L[200], XS_T2L[200], XS_StatErr_T2L[200], XS_SystErr_T2L[200], XS_MC_T2L[200];
	Double_t XS_Sum_T2L = 0.0, XS_StatErr_Sum_T2L = 0.0, XS_SystErr_Sum_T2L = 0.0; Int_t fSum_T2L = 0;
	int Count_T2L = 0, J_T2L =-1;
	for(int i=0;i<Count_T2L1;i++){
		XS_Sum_T2L = XS_T2L1[i];
		XS_StatErr_Sum_T2L = 1./pow(XS_StatErr_T2L1[i]/XS_T2L1[i],2);//N1
		XS_SystErr_Sum_T2L = pow(XS_SystErr_T2L1[i]/XS_T2L1[i],2);
		fSum_T2L = 1;
		//if(bMore_T2L2){
		for(int j=0;j<Count_T2L2;j++){
			//Find the verlapping bin for two setting, such as Kin3.1 and Kin3.2
			if(abs(Xbj_T2L1[i]-Xbj_T2L2[j])< 0.0001){
				XS_Sum_T2L += XS_T2L2[j];
				XS_StatErr_Sum_T2L +=	1./pow(XS_StatErr_T2L2[j]/XS_T2L2[j],2);//N1+N2
				XS_SystErr_Sum_T2L +=	pow(XS_SystErr_T2L2[j]/XS_T2L2[j],2);
				fSum_T2L++; J_T2L = j;
				break; //No two xbj bin within one setting
			}
		}
		//}
		Ep_T2L[i] = Ep_T2L1[i];
		Xbj_T2L[i] = Xbj_T2L1[i];
		XS_MC_T2L[i] = XS_MC_T2L1[i];
		XS_T2L[i] = XS_Sum_T2L / fSum_T2L;
		XS_StatErr_T2L[i] = XS_T2L[i] * 1./sqrt(XS_StatErr_Sum_T2L);//1/sqrt(N1+N2) 
		XS_SystErr_T2L[i] = XS_T2L[i] * sqrt(XS_SystErr_Sum_T2L) / fSum_T2L; 
		Count_T2L++;
	}
	for(int k=J_T2L+1;k<Count_T2L2;k++){
		Ep_T2L[Count_T2L] = Ep_T2L2[k];
		Xbj_T2L[Count_T2L] = Xbj_T2L2[k];
		XS_T2L[Count_T2L] = XS_T2L2[k];
		XS_StatErr_T2L[Count_T2L] = XS_StatErr_T2L2[k];
		XS_SystErr_T2L[Count_T2L] = XS_SystErr_T2L2[k];
		XS_MC_T2L[Count_T2L] = XS_MC_T2L2[k];
		Count_T2L++;	
	}
	/*}}}*/
	/*Add Last Two Input{{{*/
	Double_t Ep_T2R[200], Xbj_T2R[200], XS_T2R[200], XS_StatErr_T2R[200], XS_SystErr_T2R[200], XS_MC_T2R[200];
	Double_t XS_Sum_T2R = 0.0, XS_StatErr_Sum_T2R = 0.0, XS_SystErr_Sum_T2R = 0.0; Int_t fSum_T2R = 0;
	int Count_T2R = 0, J_T2R =-1;
	//if(bMore_T2R1){
	for(int i=0;i<Count_T2R1;i++){
		XS_Sum_T2R = XS_T2R1[i];
		XS_StatErr_Sum_T2R = 1./pow(XS_StatErr_T2R1[i]/XS_T2R1[i],2);//N1
		XS_SystErr_Sum_T2R = pow(XS_SystErr_T2R1[i]/XS_T2R1[i],2);
		fSum_T2R = 1;
		if(bMore_T2R2){
			for(int j=0;j<Count_T2R2;j++){
				//Find the verlapping bin for two setting, such as Kin3.1 and Kin3.2
				if(abs(Xbj_T2R1[i]-Xbj_T2R2[j])< 0.0001){
					XS_Sum_T2R += XS_T2R2[j];
					XS_StatErr_Sum_T2R +=	1./pow(XS_SystErr_T2R2[j]/XS_T2R2[j],2);//N1+N2
					XS_SystErr_Sum_T2R +=	pow(XS_StatErr_T2R2[j]/XS_T2R2[j],2);
					fSum_T2R++; J_T2R = j;
					break; //No two xbj bin within one setting
				}
			}
		}
		Ep_T2R[i] = Ep_T2R1[i];
		Xbj_T2R[i] = Xbj_T2R1[i];
		XS_MC_T2R[i] = XS_MC_T2R1[i];
		XS_T2R[i] = XS_Sum_T2R / fSum_T2R;
		XS_StatErr_T2R[i] = XS_T2R[i] * 1./sqrt(XS_StatErr_Sum_T2R);//1/sqrt(N1+N2) 
		XS_SystErr_T2R[i] = XS_T2R[i] * sqrt(XS_SystErr_Sum_T2R) / fSum_T2R; 
		Count_T2R++;
	}
	for(int k=J_T2R+1;k<Count_T2R2;k++){
		Ep_T2R[Count_T2R] = Ep_T2R2[k];
		Xbj_T2R[Count_T2R] = Xbj_T2R2[k];
		XS_T2R[Count_T2R] = XS_T2R2[k];
		XS_MC_T2R[Count_T2R] = XS_MC_T2R2[k];
		XS_StatErr_T2R[Count_T2R] = XS_StatErr_T2R2[k];
		XS_SystErr_T2R[Count_T2R] = XS_SystErr_T2R2[k];
		Count_T2R++;	
	}
	//}
	/*}}}*/

	/*Add All{{{*/
	/*
	double T2_Syst_Err_Com = (T2L1_Syst_Err+T2L2_Syst_Err+T2R1_Syst_Err+T2R2_Syst_Err)/4.0;
	vector<double> vEp2, vXbj2, vXbj_Err2, vXS2, vXS_Err2, vXS_MC2;
	vector<double> vXS2_StatErr, vXS2_LTQEErr, vXS2_SystErr;
	double XS_MC_T2, XS_T2,XS_Err_T2;
	double X_Min2 = 100.0, X_Max2 = -100.0, Y_Min2 = 10000.0, Y_Max2 = -10000.0;
	int N2 = 0, J2R = 0;
	bool bFound_T2L = kFALSE;
	if(Xbj_T2L[0]<Xbj_T2R[0]){
		for(int i=0;i<Count_T2L; i++){
			bFound_T2L = kFALSE;
			for(int j=0;j<Count_T2R; j++){
				if( abs(Xbj_T2L[i] - Xbj_T2R[j])<0.0001 ){
					bFound_T2L = kTRUE;
					vEp2.push_back(Ep_T2L[i]);	
					vXbj2.push_back(Xbj_T2L[i]);	
					vXbj_Err2.push_back(0.0);	
					XS_T2 = (XS_T2L[i]+XS_T2R[j])/2.0;
					XS_Err_T2 = (pow(XS_StatErr_T2L[i]/XS_T2L[i],2) + pow(XS_StatErr_T2R[j]/XS_T2R[j],2))/2.0;
					XS_Err_T2 +=(pow(XS_SystErr_T2L[i]/XS_T2L[i],2) + pow(XS_SystErr_T2R[j]/XS_T2R[j],2))/2.0;
					XS_Err_T2 +=pow(T2_Syst_Err_Com,2);
					XS_Err_T2 = XS_T2 * sqrt(XS_Err_T2);
					XS_MC_T2 = (XS_MC_T2L[i]+XS_MC_T2R[j])/2.0;

					vXS2_StatErr.push_back(XS_T2 * sqrt( (pow(XS_StatErr_T2L[i]/XS_T2L[i],2) + pow(XS_StatErr_T2R[j]/XS_T2R[j],2))/2.0) );
					vXS2_LTQEErr.push_back(XS_T2 * sqrt( (pow(XS_SystErr_T2L[i]/XS_T2L[i],2) + pow(XS_SystErr_T2R[j]/XS_T2R[j],2))/2.0) );
					vXS2_SystErr.push_back(XS_T2 * T2_Syst_Err_Com);
					
					vXS2.push_back(XS_T2);
					vXS_Err2.push_back(XS_Err_T2);
					vXS_MC2.push_back( XS_MC_T2 );
					N2++; J2R = j;

					if(Xbj_T2L[i] < X_Min2)
						X_Min2 = Xbj_T2L[i];
					if(Xbj_T2L[i] > X_Max2)
						X_Max2 = Xbj_T2L[i];
					if(XS_T2 < Y_Min2)
						Y_Min2 = XS_T2;
					if(XS_T2 > Y_Max2)
						Y_Max2 = XS_T2;
					if(XS_MC_T2 < Y_Min2)
						Y_Min2 = XS_MC_T2;
					if(XS_T2 > Y_Max2)
						Y_Max2 = XS_MC_T2;
				}
			}
			if(!bFound_T2L){
				vEp2.push_back(Ep_T2L[i]);	
				vXbj2.push_back(Xbj_T2L[i]);	
				vXbj_Err2.push_back(0.0);	
				XS_T2 = XS_T2L[i];
				XS_Err_T2 = pow(XS_StatErr_T2L[i]/XS_T2L[i],2);
				XS_Err_T2 += pow(XS_SystErr_T2L[i]/XS_T2L[i],2);
				XS_Err_T2 += pow(T2_Syst_Err_Com,2);
				XS_Err_T2 = XS_T2 * sqrt(XS_Err_T2);

				XS_MC_T2 = XS_MC_T2L[i];

				vXS2_StatErr.push_back(XS_StatErr_T2L[i]);
				vXS2_LTQEErr.push_back(XS_SystErr_T2L[i]);
				vXS2_SystErr.push_back(XS_T2 * T2_Syst_Err_Com);

					
				vXS2.push_back(XS_T2);
				vXS_Err2.push_back(XS_Err_T2);
				vXS_MC2.push_back( XS_MC_T2 );
				N2++;

				if(Xbj_T2L[i] < X_Min2)
					X_Min2 = Xbj_T2L[i];
				if(Xbj_T2L[i] > X_Max2)
					X_Max2 = Xbj_T2L[i];
				if(XS_T2 < Y_Min2)
					Y_Min2 = XS_T2;
				if(XS_T2 > Y_Max2)
					Y_Max2 = XS_T2;
				if(XS_MC_T2 < Y_Min2)
					Y_Min2 = XS_MC_T2;
				if(XS_T2 > Y_Max2)
					Y_Max2 = XS_MC_T2;
			}
		}
		for(int k = J2R+1; k<Count_T2R; k++){
			vEp2.push_back(Ep_T2R[k]);	
			vXbj2.push_back(Xbj_T2R[k]);	
			vXbj_Err2.push_back(0.0);	
			XS_T2 = XS_T2R[k];
			XS_Err_T2 = pow(XS_StatErr_T2R[k]/XS_T2R[k],2);
			XS_Err_T2 += pow(XS_SystErr_T2R[k]/XS_T2R[k],2);
			XS_Err_T2 += pow(T2_Syst_Err_Com,2);
			XS_Err_T2 = XS_T2 * sqrt(XS_Err_T2);

			XS_MC_T2 = XS_MC_T2R[k];

			vXS2_StatErr.push_back(XS_StatErr_T2R[k]);
			vXS2_LTQEErr.push_back(XS_SystErr_T2R[k]);
			vXS2_SystErr.push_back(XS_T2 * T2_Syst_Err_Com);
					
			vXS2.push_back(XS_T2);
			vXS_Err2.push_back(XS_Err_T2);
			vXS_MC2.push_back( XS_MC_T2 );
			N2++;

			if(Xbj_T2R[k] < X_Min2)
				X_Min2 = Xbj_T2R[k];
			if(Xbj_T2R[k] > X_Max2)
				X_Max2 = Xbj_T2R[k];
			if(XS_T2 < Y_Min2)
				Y_Min2 = XS_T2;
			if(XS_T2 > Y_Max2)
				Y_Max2 = XS_T2;
			if(XS_MC_T2 < Y_Min2)
				Y_Min2 = XS_MC_T2;
			if(XS_T2 > Y_Max2)
				Y_Max2 = XS_MC_T2;
		}
	}
	else{
		int J2L=0; bool bFound_T2R = kFALSE;
		for(int i=0;i<Count_T2R; i++){
			bFound_T2R = kFALSE;
			for(int j=0;j<Count_T2L; j++){
				if( abs(Xbj_T2R[i] - Xbj_T2L[j])<0.0001 ){
					bFound_T2R = kTRUE;
					vEp2.push_back(Ep_T2R[i]);	
					vXbj2.push_back(Xbj_T2R[i]);	
					vXbj_Err2.push_back(0.0);	
					XS_T2 = (XS_T2R[i]+XS_T2L[j])/2.0;
					XS_Err_T2 = (pow(XS_StatErr_T2R[i]/XS_T2R[i],2) + pow(XS_StatErr_T2L[j]/XS_T2L[j],2))/2.0;
					XS_Err_T2 +=(pow(XS_SystErr_T2R[i]/XS_T2R[i],2) + pow(XS_SystErr_T2L[j]/XS_T2L[j],2))/2.0;
					XS_Err_T2 +=pow(T2_Syst_Err_Com,2);
					XS_Err_T2 = XS_T2 * sqrt(XS_Err_T2);

					XS_MC_T2 = (XS_MC_T2R[i]+XS_MC_T2L[j])/2.0;

					vXS2_StatErr.push_back(XS_T2 * sqrt( (pow(XS_StatErr_T2L[j]/XS_T2L[j],2) + pow(XS_StatErr_T2R[i]/XS_T2R[i],2))/2.0) );
					vXS2_LTQEErr.push_back(XS_T2 * sqrt( (pow(XS_SystErr_T2L[j]/XS_T2L[j],2) + pow(XS_SystErr_T2R[i]/XS_T2R[i],2))/2.0) );
					vXS2_SystErr.push_back(XS_T2 * T2_Syst_Err_Com);
					
					vXS2.push_back(XS_T2);
					vXS_Err2.push_back(XS_Err_T2);
					vXS_MC2.push_back( XS_MC_T2 );
					N2++; J2L = j;

					if(Xbj_T2R[i] < X_Min2)
						X_Min2 = Xbj_T2R[i];
					if(Xbj_T2R[i] > X_Max2)
						X_Max2 = Xbj_T2R[i];
					if(XS_T2 < Y_Min2)
						Y_Min2 = XS_T2;
					if(XS_T2 > Y_Max2)
						Y_Max2 = XS_T2;
					if(XS_MC_T2 < Y_Min2)
						Y_Min2 = XS_MC_T2;
					if(XS_T2 > Y_Max2)
						Y_Max2 = XS_MC_T2;
				}
			}
			if(!bFound_T2R){
				vEp2.push_back(Ep_T2R[i]);	
				vXbj2.push_back(Xbj_T2R[i]);	
				vXbj_Err2.push_back(0.0);	
				XS_T2 = XS_T2R[i];
				XS_Err_T2 = pow(XS_StatErr_T2R[i]/XS_T2R[i],2);
				XS_Err_T2 += pow(XS_SystErr_T2R[i]/XS_T2R[i],2);
				XS_Err_T2 += pow(T2_Syst_Err_Com,2);
				XS_Err_T2 = XS_T2 * sqrt(XS_Err_T2);

				XS_MC_T2 = XS_MC_T2R[i];

				vXS2_StatErr.push_back(XS_StatErr_T2R[i]);
				vXS2_LTQEErr.push_back(XS_SystErr_T2R[i]);
				vXS2_SystErr.push_back(XS_T2 * T2_Syst_Err_Com);

				vXS2.push_back(XS_T2);
				vXS_Err2.push_back(XS_Err_T2);
				vXS_MC2.push_back( XS_MC_T2 );
				N2++;

				if(Xbj_T2R[i] < X_Min2)
					X_Min2 = Xbj_T2R[i];
				if(Xbj_T2R[i] > X_Max2)
					X_Max2 = Xbj_T2R[i];
				if(XS_T2 < Y_Min2)
					Y_Min2 = XS_T2;
				if(XS_T2 > Y_Max2)
					Y_Max2 = XS_T2;
				if(XS_MC_T2 < Y_Min2)
					Y_Min2 = XS_MC_T2;
				if(XS_T2 > Y_Max2)
					Y_Max2 = XS_MC_T2;
			}
		}
		for(int k = J2L+1; k<Count_T2L; k++){
			vEp2.push_back(Ep_T2L[k]);	
			vXbj2.push_back(Xbj_T2L[k]);	
			vXbj_Err2.push_back(0.0);	
			XS_T2 = XS_T2L[k];
			XS_Err_T2 = pow(XS_StatErr_T2L[k]/XS_T2L[k],2);
			XS_Err_T2 += pow(XS_SystErr_T2L[k]/XS_T2L[k],2);
			XS_Err_T2 += pow(T2_Syst_Err_Com,2);
			XS_Err_T2 = XS_T2 * sqrt(XS_Err_T2);

			XS_MC_T2 = XS_MC_T2L[k];

			vXS2_StatErr.push_back(XS_StatErr_T2L[k]);
			vXS2_LTQEErr.push_back(XS_SystErr_T2L[k]);
			vXS2_SystErr.push_back(XS_T2 * T2_Syst_Err_Com);

			vXS2.push_back(XS_T2);
			vXS_Err2.push_back(XS_Err_T2);
			vXS_MC2.push_back( XS_MC_T2 );
			N2++;

			if(Xbj_T2L[k] < X_Min2)
				X_Min2 = Xbj_T2L[k];
			if(Xbj_T2L[k] > X_Max2)
				X_Max2 = Xbj_T2L[k];
			if(XS_T2 < Y_Min2)
				Y_Min2 = XS_T2;
			if(XS_T2 > Y_Max2)
				Y_Max2 = XS_T2;
			if(XS_MC_T2 < Y_Min2)
				Y_Min2 = XS_MC_T2;
			if(XS_T2 > Y_Max2)
				Y_Max2 = XS_MC_T2;
		}
	}
	*/
	/*}}}*/
	/*OLD-Add All{{{*/
	double T2_Syst_Err_Com = (T2L1_Syst_Err+T2L2_Syst_Err+T2R1_Syst_Err+T2R2_Syst_Err)/4.0;
	vector<double> vEp2, vXbj2, vXbj_Err2, vXS2, vXS_Err2, vXS_MC2;
	vector<double> vXS2_StatErr, vXS2_LTQEErr, vXS2_SystErr;
	double XS_MC_T2, XS_T2,XS_Err_T2;
	double X_Min2 = 100.0, X_Max2 = -100.0, Y_Min2 = 10000.0, Y_Max2 = -10000.0;
	int N2 = 0, J2R = 0;
	bool bFound_T2L = kFALSE;
	if(bMore_T2R1){
		for(int i=0;i<Count_T2L; i++){
			bFound_T2L = kFALSE;
			for(int j=0;j<Count_T2R; j++){
				if( abs(Xbj_T2L[i] - Xbj_T2R[j])<0.0001 ){
					bFound_T2L = kTRUE;
					vEp2.push_back(Ep_T2L[i]);	
					vXbj2.push_back(Xbj_T2L[i]);	
					vXbj_Err2.push_back(0.0);	
					XS_T2 = (XS_T2L[i]+XS_T2R[j])/2.0;
					XS_Err_T2 = 1./(1./pow(XS_StatErr_T2L[i]/XS_T2L[i],2) + 1./pow(XS_StatErr_T2R[j]/XS_T2R[j],2))/2.0;//1/(N1+N2)
					XS_Err_T2 +=(pow(XS_SystErr_T2L[i]/XS_T2L[i],2) + pow(XS_SystErr_T2R[j]/XS_T2R[j],2))/2.0;
					XS_Err_T2 +=pow(T2_Syst_Err_Com,2);
					XS_Err_T2 = XS_T2 * sqrt(XS_Err_T2);

					XS_MC_T2 = (XS_MC_T2L[i]+XS_MC_T2R[j])/2.0;

					vXS2_StatErr.push_back(1./sqrt( (1./pow(XS_StatErr_T2L[i]/XS_T2L[i],2) + 1./pow(XS_StatErr_T2R[j]/XS_T2R[j],2))) );
					vXS2_LTQEErr.push_back(sqrt( (pow(XS_SystErr_T2L[i]/XS_T2L[i],2) + pow(XS_SystErr_T2R[j]/XS_T2R[j],2))/2.0) );
					vXS2_SystErr.push_back(T2_Syst_Err_Com);
					
					vXS2.push_back(XS_T2);
					vXS_Err2.push_back(XS_Err_T2);
					vXS_MC2.push_back( XS_MC_T2 );
					N2++; J2R = j;

					if(Xbj_T2L[i] < X_Min2)
						X_Min2 = Xbj_T2L[i];
					if(Xbj_T2L[i] > X_Max2)
						X_Max2 = Xbj_T2L[i];
					if(XS_T2 < Y_Min2)
						Y_Min2 = XS_T2;
					if(XS_T2 > Y_Max2)
						Y_Max2 = XS_T2;
					if(XS_MC_T2 < Y_Min2)
						Y_Min2 = XS_MC_T2;
					if(XS_T2 > Y_Max2)
						Y_Max2 = XS_MC_T2;
				}
			}
			if(!bFound_T2L){
				vEp2.push_back(Ep_T2L[i]);	
				vXbj2.push_back(Xbj_T2L[i]);	
				vXbj_Err2.push_back(0.0);	
				XS_T2 = XS_T2L[i];
				XS_Err_T2 = pow(XS_StatErr_T2L[i]/XS_T2L[i],2);
				XS_Err_T2 += pow(XS_SystErr_T2L[i]/XS_T2L[i],2);
				XS_Err_T2 += pow(T2_Syst_Err_Com,2);
				XS_Err_T2 = XS_T2 * sqrt(XS_Err_T2);

				XS_MC_T2 = XS_MC_T2L[i];

				vXS2_StatErr.push_back(XS_StatErr_T2L[i]/XS_T2L[i]);
				vXS2_LTQEErr.push_back(XS_SystErr_T2L[i]/XS_T2L[i]);
				vXS2_SystErr.push_back(T2_Syst_Err_Com);

				vXS2.push_back(XS_T2);
				vXS_Err2.push_back(XS_Err_T2);
				vXS_MC2.push_back( XS_MC_T2 );
				N2++;

				if(Xbj_T2L[i] < X_Min2)
					X_Min2 = Xbj_T2L[i];
				if(Xbj_T2L[i] > X_Max2)
					X_Max2 = Xbj_T2L[i];
				if(XS_T2 < Y_Min2)
					Y_Min2 = XS_T2;
				if(XS_T2 > Y_Max2)
					Y_Max2 = XS_T2;
				if(XS_MC_T2 < Y_Min2)
					Y_Min2 = XS_MC_T2;
				if(XS_T2 > Y_Max2)
					Y_Max2 = XS_MC_T2;
			}
		}
		for(int k = J2R+1; k<Count_T2R; k++){
			vEp2.push_back(Ep_T2R[k]);	
			vXbj2.push_back(Xbj_T2R[k]);	
			vXbj_Err2.push_back(0.0);	
			XS_T2 = XS_T2R[k];
			XS_Err_T2 = pow(XS_StatErr_T2R[k]/XS_T2R[k],2);
			XS_Err_T2 += pow(XS_SystErr_T2R[k]/XS_T2R[k],2);
			XS_Err_T2 += pow(T2_Syst_Err_Com,2);
			XS_Err_T2 = XS_T2 * sqrt(XS_Err_T2);

			XS_MC_T2 = XS_MC_T2R[k];

			vXS2_StatErr.push_back(XS_StatErr_T2R[k]/XS_T2R[k]);
			vXS2_LTQEErr.push_back(XS_SystErr_T2R[k]/XS_T2R[k]);
			vXS2_SystErr.push_back(T2_Syst_Err_Com);

			vXS2.push_back(XS_T2);
			vXS_Err2.push_back(XS_Err_T2);
			vXS_MC2.push_back( XS_MC_T2 );
			N2++;

			if(Xbj_T2R[k] < X_Min2)
				X_Min2 = Xbj_T2R[k];
			if(Xbj_T2R[k] > X_Max2)
				X_Max2 = Xbj_T2R[k];
			if(XS_T2 < Y_Min2)
				Y_Min2 = XS_T2;
			if(XS_T2 > Y_Max2)
				Y_Max2 = XS_T2;
			if(XS_MC_T2 < Y_Min2)
				Y_Min2 = XS_MC_T2;
			if(XS_T2 > Y_Max2)
				Y_Max2 = XS_MC_T2;
		}
	}
	else{
		for(int i=0;i<Count_T2L; i++){
			vEp2.push_back(Ep_T2L[i]);	
			vXbj2.push_back(Xbj_T2L[i]);	
			vXbj_Err2.push_back(0.0);	
			XS_T2 = XS_T2L[i];
			XS_Err_T2 = pow(XS_StatErr_T2L[i]/XS_T2L[i],2);
			XS_Err_T2 += pow(XS_SystErr_T2L[i]/XS_T2L[i],2);
			XS_Err_T2 += pow(T2_Syst_Err_Com,2);
			XS_Err_T2 = XS_T2 * sqrt(XS_Err_T2);

			XS_MC_T2 = XS_MC_T2L[i];

			vXS2_StatErr.push_back(XS_StatErr_T2L[i]/XS_T2L[i]);
			vXS2_LTQEErr.push_back(XS_SystErr_T2L[i]/XS_T2L[i]);
			vXS2_SystErr.push_back(T2_Syst_Err_Com);

			vXS2.push_back(XS_T2);
			vXS_Err2.push_back(XS_Err_T2);
			vXS_MC2.push_back( XS_MC_T2 );
			N2++;

			if(Xbj_T2L[i] < X_Min2)
				X_Min2 = Xbj_T2L[i];
			if(Xbj_T2L[i] > X_Max2)
				X_Max2 = Xbj_T2L[i];
			if(XS_T2 < Y_Min2)
				Y_Min2 = XS_T2;
			if(XS_T2 > Y_Max2)
				Y_Max2 = XS_T2;
			if(XS_MC_T2 < Y_Min2)
				Y_Min2 = XS_MC_T2;
			if(XS_T2 > Y_Max2)
				Y_Max2 = XS_MC_T2;
		}
	}
	/*}}}*/

	/*RadCorr for He3 at x>2.45{{{*/
	if(Target=="He3"){
		for(unsigned int i=0;i<vXbj2.size(); i++){
			if(vXbj2[i]>=2.45){	
				aRadCorr = gGet_RadCorr_He3(vXbj2[i]);
				cerr<<Form("++++++ xbj = %f, radcor = %f", vXbj2[i], aRadCorr)<<endl;
				vXS2[i]*=aRadCorr;
				vXS_Err2[i]*=aRadCorr;
			}
		}
	}
	/*}}}*/

	/*}}}*/

	/*Plot{{{*/
	TCanvas *c2 = new TCanvas("c2","c2",1200,800);
	gPad->SetLogy(1);
	TH2F* xs2 = new TH2F("xs2","",1000,0.7,3.2,1000,Y_Min2/2.,Y_Max2*2.0);
	xs2->SetStats(kFALSE);
	xs2->SetXTitle("x");
	xs2->GetXaxis()->CenterTitle(1);
	xs2->GetXaxis()->SetTitleFont(22);
	xs2->GetXaxis()->SetTitleSize(0.06);
	xs2->SetYTitle("#frac{d#sigma}{dE'd#Omega} (nb/MeV/sr)");
	xs2->GetYaxis()->CenterTitle(1);
	xs2->GetYaxis()->SetTitleFont(22);
	xs2->GetYaxis()->SetTitleSize(0.04);
	xs2->Draw(); 

	TGraphErrors *pl_x2 = new TGraphErrors(N2,&vXbj2[0],&vXS2[0],&vXbj_Err2[0],&vXS_Err2[0]);
	pl_x2-> SetMarkerColor(2);
	pl_x2-> SetMarkerSize(1.0);
	pl_x2-> SetMarkerStyle(22);
	pl_x2-> GetXaxis()->SetTitle("x");
	pl_x2-> GetYaxis()->SetTitle("#sigma");
	pl_x2-> Draw("P");

	TGraphErrors *pl_x21 = new TGraphErrors(N2,&vXbj2[0],&vXS_MC2[0],&vXbj_Err2[0],&vXbj_Err2[0]);
	pl_x21-> SetMarkerColor(0);
	pl_x21-> SetMarkerSize(0.0);
	pl_x21-> SetLineColor(4);
	pl_x21-> SetLineWidth(2);
	pl_x21-> SetMarkerStyle(20);
	pl_x21-> GetXaxis()->SetTitle("x");
	pl_x21-> GetYaxis()->SetTitle("#sigma_{mc}");
	pl_x21-> Draw("L");

	TLegend *l2 = new TLegend(0.65,0.57,0.90, 0.90,Form("%s Target",Target.Data()));
	l2->SetTextSize(0.03);
	l2->SetTextFont(22);
	l2->AddEntry(pl_x2,  Form("XS_{EX} at %3.1f^{#circ}",Theta),"p");
	pl_x2->Draw("P");
	l2->AddEntry(pl_x21, Form("XS_{MC} at %3.1f^{#circ}",Theta),"l");
	pl_x21->Draw("L");
	l2->Draw();

	if(aInputFileName.Contains("QE")){
		c2->Print(Form("./%s/XS_%s_%2.0f_QE_%s.png",OutFile_Dir.Data(),  Target.Data(), Theta,Com.Data()));
		c2->Print(Form("./%s/XS_%s_%2.0f_QE_%s.pdf",OutFile_Dir.Data(),  Target.Data(), Theta,Com.Data()));
	}
	else{
		c2->Print(Form("./%s/XS_%s_%2.0f_%s.png",OutFile_Dir.Data(),  Target.Data(), Theta,Com.Data()));
		c2->Print(Form("./%s/XS_%s_%2.0f_%s.pdf",OutFile_Dir.Data(),  Target.Data(), Theta,Com.Data()));
	}
	/*}}}*/
	/*}}}*/

	/*Ratio{{{*/  
	double Ratio_Syst_Err = gGet_Ratio_SystErr(Target1.Data(),Target2.Data());

	ofstream outfile(Form("./%s/XS_%s_%s_%s_%s_%s.dat",OutFile_Dir.Data(), Kin0.Data(),Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	outfile << Form("%7s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s", 
			"Xbj","Ratio","Ratio_TotalErr","Ratio_StatErr(rltv)","Ratio_SystErr(rltv)",
			"XS1","XS1_StatErr(rltv)","XS1_LTQEErr(rltv)","XS1_SystErr(rltv)",
			"XS2","XS2_StatErr(rltv)","XS2_LTQEErr(rltv)","XS2_SystErr(rltv)", "Ratio_MC", "XS1_MC", "XS2_MC" )<<endl;

	int Count=0;
	Double_t x1,x2,ep1,ratio,ratio_mc,err, syst_err, stat_err;
	vector<Double_t> vEp, vXbj, vXbj_Err,vR, vR_Err,vR_MC;

	Double_t X_Min = 10, X_Max = -10, R_Min = 1000.0, R_Max = -1000.0;
	int i,j; 
	for( i=0;i<N1;i++){
		x1 = vXbj1[i];
		ep1 = vEp1[i];
		for( j=0;j<N2;j++){
			x2 = vXbj2[j];
			//ep2 = vEp2[j];
			if(x1>=0.5&&x2>=0.5&&abs(x1-x2)<0.0001){
				if(Target1=="Ca48"&&Target2=="Ca40"){//Ca48 actually have 90% of Ca48+10% of Ca40
					vXS1[i] = ((vXS1[i]-0.1*vXS2[j])/0.9);
				}
				if(Target1=="Ca40"&&Target2=="Ca48"){//Ca48 actually have 90% of Ca48+10% of Ca40
					vXS2[j] = ((vXS2[j]-0.1*vXS1[i])/0.9);
				}
				ratio = factor*vXS1[i]/vXS2[j];
                                //actually stat_err includes both stat_err and LT_sys and Ne_sys
                                stat_err = sqrt( pow(vXS_Err2[j]/vXS2[j],2)-pow(T1_Syst_Err_Com,2) //only stat+LT_sys+Ne_sys
						+ pow(vXS_Err1[i]/vXS1[i],2)-pow(T2_Syst_Err_Com,2));
				syst_err =  Ratio_Syst_Err;
                                err = ratio* sqrt( stat_err*stat_err + syst_err*syst_err );

				ratio_mc = factor*vXS_MC2[i]/vXS_MC1[j];

				if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
					vEp.push_back(ep1);
					vXbj.push_back(x1);
					vXbj_Err.push_back(0.0);
					vR.push_back(ratio);
					vR_MC.push_back(ratio_mc);
					vR_Err.push_back(err);
					//vR_Err.push_back(ratio*stat_err);//keep the normalized error outside
					cerr <<Form("-----> Found one: xbj1=%f, xbj2=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
							x1,x2,vXS1[i],vXS2[j],factor*vXS1[i]/vXS2[j], stat_err, syst_err)<<endl;

					if(R_Min > ratio)
						R_Min = ratio;
					if(R_Min > ratio_mc)
						R_Min = ratio_mc;
					if(R_Max < ratio)
						R_Max = ratio;
					//				if(R_Max < ratio_mc)
					//					R_Max = ratio_mc;
					if(X_Min > x1)
						X_Min = x1;
					if(X_Max < x1)
						X_Max = x1;
					Count++;
					outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
							x1,ratio,err, stat_err, syst_err, 
							vXS1[i], vXS1_StatErr[i], vXS1_LTQEErr[i],vXS1_SystErr[i],
							vXS2[j], vXS2_StatErr[j], vXS2_LTQEErr[j],vXS2_SystErr[j], ratio_mc, vXS_MC1[i],vXS_MC2[j] )<<endl;
				}
			}
			}
		}

		//Return the value
		for(int k=0; k<Count; k++){
			aXbj[k] = vXbj[k];
			aR_EX[k] = vR[k];
			aR_EX_Err[k] = vR_Err[k];
			aR_MC[k] = vR_MC[k];
		}
		aN[0] = Count;
		cerr<<Form("****In Merge ******* T1_Syst_Com=%f, T2_Sys_Com=%f, Factor =%f ",T1_Syst_Err_Com, T2_Syst_Err_Com, factor)<<endl;
		outfile.close();
		/*}}}*/

                out_err.close();
}
/*}}}*/
/*}}}*/

/*Merge25{{{*/
void Merge25(const TString& Target0, const TString& Target, double* aXbj, double* aR_EX, double* aR_EX_Err, double* aR_MC, int* aN){

	ofstream outfile(Form("./%s/XS_5.0_%s_%s_%s_%s_Total.dat",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	ifstream infile1(Form("./%s/XS_5.0_%s_%s_%s_%s.dat",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	ifstream infile2(Form("./%s/XS_5.1_%s_%s_%s_%s.dat",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));

	outfile << Form("%7s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s", 
			"Xbj","Ratio","Ratio_TotalErr","Ratio_StatErr(rltv)","Ratio_SystErr(rltv)",
			"XS1","XS1_StatErr(rltv)","XS1_LTQEErr(rltv)","XS1_SystErr(rltv)",
			"XS2","XS2_StatErr(rltv)","XS2_LTQEErr(rltv)","XS2_SystErr(rltv)", "Ratio_MC", "XS1_MC", "XS2_MC" )<<endl;

	vector<double> vXbj1, vXS11,vRatio_SystErr1, vXS11_StatErr, vXS11_LTQEErr,vXS11_SystErr, vXS12, vXS21_StatErr, vXS21_LTQEErr,vXS21_SystErr;
	vector<double> vXbj2, vXS21,vRatio_SystErr2, vXS12_StatErr, vXS12_LTQEErr,vXS12_SystErr, vXS22, vXS22_StatErr, vXS22_LTQEErr,vXS22_SystErr;
	vector<double> vRatio_MC, vXS11_MC, vXS21_MC, vXS12_MC, vXS22_MC;

    /*Readin{{{*/
	double x, R, R_err, R_systerr, R_staterr,xs1, xs1_staterr,xs1_ltqeerr, xs1_systerr,xs2, xs2_staterr,xs2_ltqeerr, xs2_systerr,R_MC, xs1_mc, xs2_mc;
	TString dum;
	infile1 >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum>>dum >>dum >>dum;
	while(infile1 >> x >> R >> R_err >> R_staterr >> R_systerr >> xs1>> xs1_staterr>>xs1_ltqeerr>>xs1_systerr>>xs2>> xs2_staterr>>xs2_ltqeerr>>xs2_systerr>>R_MC>>xs1_mc>>xs2_mc){

		cerr<<Form("Kin5.0: x=%6.4f,  R = %6.4f, R_Err = %6.4f", x, R, R_err)<<endl;;
		vXbj1.push_back(x);
		vRatio_SystErr1.push_back(R_systerr);

		vXS11.push_back(xs1);
		vXS11_MC.push_back(xs1_mc);
		vXS11_StatErr.push_back(xs1_staterr);
		vXS11_SystErr.push_back(xs1_systerr);
		vXS11_LTQEErr.push_back(xs1_ltqeerr);
		vXS21.push_back(xs2);
		vXS21_MC.push_back(xs2_mc);
		vXS21_StatErr.push_back(xs2_staterr);
		vXS21_SystErr.push_back(xs2_systerr);
		vXS21_LTQEErr.push_back(xs2_ltqeerr);
	}
	infile1.close();

	infile2 >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum;
	while(infile2 >> x >> R >> R_err >> R_staterr >> R_systerr >> xs1>> xs1_staterr>>xs1_ltqeerr>>xs1_systerr>>xs2>> xs2_staterr>>xs2_ltqeerr>>xs2_systerr>>R_MC>>xs1_mc>>xs2_mc){
		cerr<<Form("Kin5.1: x=%6.4f,  R = %6.4f, R_Err = %6.4f", x, R, R_err)<<endl;;
		vXbj2.push_back(x);
		vRatio_SystErr2.push_back(R_systerr);

		vXS12.push_back(xs1);
		vXS12_MC.push_back(xs1_mc);
		vXS12_StatErr.push_back(xs1_staterr);
		vXS12_SystErr.push_back(xs1_systerr);
		vXS12_LTQEErr.push_back(xs1_ltqeerr);
		vXS22.push_back(xs2);
		vXS22_MC.push_back(xs2_mc);
		vXS22_StatErr.push_back(xs2_staterr);
		vXS22_SystErr.push_back(xs2_systerr);
		vXS22_LTQEErr.push_back(xs2_ltqeerr);
	}
	infile2.close();/*}}}*/

	int Count=0;
	vector<double> vXbj, vR, vR_Err, vR_StatErr, vR_SystErr,vXS1, vXS1_StatErr, vXS1_LTQEErr,vXS1_SystErr, vXS2, vXS2_StatErr, vXS2_LTQEErr,vXS2_SystErr, vR_MC, vXS1_MC, vXS2_MC;
	Double_t x1,x2,ratio,err, syst_err, stat_err, ratio_mc;

	Double_t X_Min = 10, X_Max = -10, R_Min = 1000.0, R_Max = -1000.0;
	int J2 = -1;
	bool bFound = kFALSE;

	int J20= -1;
	bool bFirst = kTRUE;

        for(unsigned int i=0;i<vXbj1.size();i++){
		x1 = vXbj1[i];
		bFound = kFALSE;
		for(unsigned int j=0;j<vXbj2.size();j++){
                    x2 = vXbj2[j];
                    /*Combine two bins{{{*/
                    if(x1>=0.5&&x2>=0.5&&abs(x1-x2)<0.0001){
                        if(bFirst){
                            bFirst = kFALSE;
                            J20= j;
                        }

                        bFound = kTRUE;
                        J2 = j;
                        double xs1 = (vXS11[i] + vXS12[j])/2.0;
                        double xs1_mc = (vXS11_MC[i] + vXS12_MC[j])/2.0;
                        double xs1_stat_err = 1./sqrt( 1./pow(vXS11_StatErr[i],2) + 1./pow(vXS12_StatErr[j],2) );
                        double xs1_syst_err = (vXS11_SystErr[i] + vXS12_SystErr[j])/2.0;
                        double xs1_ltqe_err = (vXS11_LTQEErr[i] + vXS12_LTQEErr[j])/2.0;

                        double xs2 = (vXS21[i] + vXS22[j])/2.0;
                        double xs2_mc = (vXS21_MC[i] + vXS22_MC[j])/2.0;
                        double xs2_stat_err = 1./sqrt( 1./pow(vXS21_StatErr[i],2) + 1./pow(vXS22_StatErr[j],2) );
                        double xs2_syst_err = (vXS21_SystErr[i] + vXS22_SystErr[j])/2.0;
                        double xs2_ltqe_err = (vXS21_LTQEErr[i] + vXS22_LTQEErr[j])/2.0;
                        double ratio_syst_err = (vRatio_SystErr1[i]+vRatio_SystErr2[j])/2.0;

                        ratio = factor00*xs1/xs2;
                        ratio_mc = factor00*xs1_mc/xs2_mc;
                        err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
                        //actually stat_er5 includes both stat_err and LT_sys and Ne_sys
                        stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
                        syst_err =  ratio_syst_err;

                        if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
                            vXbj.push_back(x1);

                            vXS1.push_back(xs1);
                            vXS1_MC.push_back(xs1_mc);
                            vXS1_StatErr.push_back(xs1_stat_err);
                            vXS1_SystErr.push_back(xs1_syst_err);
                            vXS1_LTQEErr.push_back(xs1_ltqe_err);

                            vXS2.push_back(xs2);
                            vXS2_MC.push_back(xs2_mc);
                            vXS2_StatErr.push_back(xs2_stat_err);
                            vXS2_SystErr.push_back(xs2_syst_err);
                            vXS2_LTQEErr.push_back(xs2_ltqe_err);

                            vR.push_back(ratio);
                            vR_MC.push_back(ratio_mc);
                            vR_Err.push_back(err);
                            //vR_Err.push_back(ratio*stat_err);
                            cerr <<Form("-----> 25^{#circ}: xbj1=%f, xbj2=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
                                    x1,x2,xs1,xs2,ratio, stat_err, syst_err)<<endl;

                            if(R_Min > ratio)
                                R_Min = ratio;
                            if(R_Max < ratio)
                                R_Max = ratio;
                            if(X_Min > x1)
                                X_Min = x1;
                            if(X_Max < x1)
                                X_Max = x1;
                            Count++;
                            outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
                                    x1,ratio,err, stat_err, syst_err, 
                                    xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
                                    xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err,ratio_mc, xs1_mc,xs2_mc )<<endl;
                        }
                    }
                    /*}}}*/
                }
                /*Don't find the bin from the second set{{{*/	
                if(!(bFound)){
                    x1 = vXbj1[i];
                    double xs1 = vXS11[i];
                    double xs1_mc = vXS11_MC[i];
                    double xs1_stat_err = vXS11_StatErr[i];
                    double xs1_syst_err = vXS11_SystErr[i];
                    double xs1_ltqe_err = vXS11_LTQEErr[i];
                    double xs2 = vXS21[i];
                    double xs2_mc = vXS21_MC[i];
                    double xs2_stat_err = pow(vXS21_StatErr[i],2);
                    double xs2_syst_err = vXS21_SystErr[i];
                    double xs2_ltqe_err = vXS21_LTQEErr[i];
                    double ratio_syst_err = vRatio_SystErr1[i];

                    ratio = factor00*xs1/xs2;
                    ratio_mc = factor00*xs1_mc/xs2_mc;
                    err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
                    //actually stat_err includes both stat_err and LT_sys and Ne_sys
                    stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
                    syst_err =  ratio_syst_err;

                    if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
                        vXbj.push_back(x1);

                        vXS1.push_back(xs1);
                        vXS1_MC.push_back(xs1_mc);
                        vXS1_StatErr.push_back(xs1_stat_err);
                        vXS1_SystErr.push_back(xs1_syst_err);
                        vXS1_LTQEErr.push_back(xs1_ltqe_err);
                        vXS2.push_back(xs2);
                        vXS2_MC.push_back(xs2_mc);
                        vXS2_StatErr.push_back(xs2_stat_err);
                        vXS2_SystErr.push_back(xs2_syst_err);
                        vXS2_LTQEErr.push_back(xs2_ltqe_err);

                        vR.push_back(ratio);
                        vR_MC.push_back(ratio_mc);
                        vR_Err.push_back(err);
                        //vR_Err.push_back(ratio*stat_err);
                        cerr <<Form("-----> Found one: xbj1=%f, xbj2=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
                                x1,x2,xs1,xs2,ratio, stat_err, syst_err)<<endl;

                        if(R_Min > ratio)
                            R_Min = ratio;
                        if(R_Max < ratio)
                            R_Max = ratio;
                        if(X_Min > x1)
                            X_Min = x1;
                        if(X_Max < x1)
                            X_Max = x1;
                        Count++;
                        outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
                                x1,ratio,err, stat_err, syst_err, 
                                xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
                                xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err,ratio_mc, xs1_mc,xs2_mc )<<endl;
                    }
                }
                /*}}}*/
	}
	/*Pickup late left over from the second set bin only{{{*/	
	for(unsigned int i=J2+1;i<vXbj2.size();i++){
		x1 = vXbj2[i];
		double xs1 = vXS12[i];
		double xs1_mc = vXS12_MC[i];
		double xs1_stat_err = vXS12_StatErr[i];
		double xs1_syst_err = vXS12_SystErr[i];
		double xs1_ltqe_err = vXS12_LTQEErr[i];
		double xs2 = vXS22[i];
		double xs2_mc = vXS22_MC[i];
		double xs2_stat_err = pow(vXS22_StatErr[i],2);
		double xs2_syst_err = vXS22_SystErr[i];
		double xs2_ltqe_err = vXS22_LTQEErr[i];
		double ratio_syst_err = vRatio_SystErr2[i];

		ratio = factor00*xs1/xs2;
		ratio_mc = factor00*xs1_mc/xs2_mc;
		err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
		//actually stat_err includes both stat_err and LT_sys and Ne_sys
		stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
		syst_err =  ratio_syst_err;

		if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
			vXbj.push_back(x1);

			vXS1.push_back(xs1);
			vXS1_MC.push_back(xs1_mc);
			vXS1_StatErr.push_back(xs1_stat_err);
			vXS1_SystErr.push_back(xs1_syst_err);
			vXS1_LTQEErr.push_back(xs1_ltqe_err);
			vXS2.push_back(xs2);
			vXS2_MC.push_back(xs2_mc);
			vXS2_StatErr.push_back(xs2_stat_err);
			vXS2_SystErr.push_back(xs2_syst_err);
			vXS2_LTQEErr.push_back(xs2_ltqe_err);

			vR.push_back(ratio);
			vR_MC.push_back(ratio_mc);
			vR_Err.push_back(err);
			//vR_Err.push_back(ratio*stat_err);
			cerr <<Form("-----> Found late one in 25: xbj1=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
					x1,xs1,xs2,ratio, stat_err, syst_err)<<endl;

			if(R_Min > ratio)
				R_Min = ratio;
			if(R_Max < ratio)
				R_Max = ratio;
			if(X_Min > x1)
				X_Min = x1;
			if(X_Max < x1)
				X_Max = x1;
			Count++;
			outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
					x1,ratio,err, stat_err, syst_err, 
					xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
					xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err, ratio_mc, xs1_mc, xs2_mc )<<endl;
		}
	}
	/*}}}*/
	
        /*Pickup early left over from the second set bin only{{{*/
        if(J20>=1){
            for(unsigned int i=0;i<J20;i++){
                x1 = vXbj2[i];
                double xs1 = vXS12[i];
                double xs1_mc = vXS12_MC[i];
                double xs1_stat_err = vXS12_StatErr[i];
                double xs1_syst_err = vXS12_SystErr[i];
                double xs1_ltqe_err = vXS12_LTQEErr[i];
                double xs2 = vXS22[i];
                double xs2_mc = vXS22_MC[i];
                double xs2_stat_err = pow(vXS22_StatErr[i],2);
                double xs2_syst_err = vXS22_SystErr[i];
                double xs2_ltqe_err = vXS22_LTQEErr[i];
                double ratio_syst_err = vRatio_SystErr2[i];

                ratio = factor00*xs1/xs2;
                ratio_mc = factor00*xs1_mc/xs2_mc;
                err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
                //actually stat_err includes both stat_err and LT_sys and Ne_sys
                stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
                syst_err =  ratio_syst_err;

                if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
                    vXbj.push_back(x1);

                    vXS1.push_back(xs1);
                    vXS1_MC.push_back(xs1_mc);
                    vXS1_StatErr.push_back(xs1_stat_err);
                    vXS1_SystErr.push_back(xs1_syst_err);
                    vXS1_LTQEErr.push_back(xs1_ltqe_err);
                    vXS2.push_back(xs2);
                    vXS2_MC.push_back(xs2_mc);
                    vXS2_StatErr.push_back(xs2_stat_err);
                    vXS2_SystErr.push_back(xs2_syst_err);
                    vXS2_LTQEErr.push_back(xs2_ltqe_err);

                    vR.push_back(ratio);
                    vR_MC.push_back(ratio_mc);
                    vR_Err.push_back(err);
                    //vR_Err.push_back(ratio*stat_err);
                    cerr <<Form("-----> Found early one in 25: xbj1=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
                            x1,xs1,xs2,ratio, stat_err, syst_err)<<endl;

                    if(R_Min > ratio)
                        R_Min = ratio;
                    if(R_Max < ratio)
                        R_Max = ratio;
                    if(X_Min > x1)
                        X_Min = x1;
                    if(X_Max < x1)
                        X_Max = x1;
                    Count++;
                    outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
                            x1,ratio,err, stat_err, syst_err, 
                            xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
                            xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err, ratio_mc, xs1_mc, xs2_mc )<<endl;
                }
            }
        }
        /*}}}*/

	//Return the value
	for(int k=0; k<Count; k++){
		aXbj[k] = vXbj[k];
		aR_EX[k] = vR[k];
		aR_EX_Err[k] = vR_Err[k];
		aR_MC[k] = vR_MC[k];
	}
	aN[0] = Count;
	cerr<<"*****In Merge25***** Factor = "<< factor00<<endl;
	outfile.close();
}
/*}}}*/

/*Merge2325{{{*/
void Merge2325(const TString& Target0, const TString& Target, double* aXbj, double* aR_EX, double* aR_EX_Err, double* aR_MC, int* aN){

	ofstream outfile(Form("./%s/XS_2325_%s_%s_%s_%s_Total.dat",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	ifstream infile1;
	infile1.open(Form("./%s/XS_5.0_%s_%s_%s_%s_Total.dat",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	ifstream infile2;
	if(Target0=="He4"||Target=="He4")
		infile2.open(Form("./%s/XS_4.2_%s_%s_%s_%s.dat",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	else
		infile2.open(Form("./%s/XS_4.1_%s_%s_%s_%s.dat",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));

	outfile << Form("%7s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s", 
			"Xbj","Ratio","Ratio_TotalErr","Ratio_StatErr(rltv)","Ratio_SystErr(rltv)",
			"XS1","XS1_StatErr(rltv)","XS1_LTQEErr(rltv)","XS1_SystErr(rltv)",
			"XS2","XS2_StatErr(rltv)","XS2_LTQEErr(rltv)","XS2_SystErr(rltv)", "Ratio_MC", "XS1_MC", "XS2_MC" )<<endl;

	vector<double> vXbj1, vXS11,vRatio_SystErr1, vXS11_StatErr, vXS11_LTQEErr,vXS11_SystErr, vXS12, vXS21_StatErr, vXS21_LTQEErr,vXS21_SystErr;
	vector<double> vXbj2, vXS21,vRatio_SystErr2, vXS12_StatErr, vXS12_LTQEErr,vXS12_SystErr, vXS22, vXS22_StatErr, vXS22_LTQEErr,vXS22_SystErr;
	vector<double> vRatio_MC, vXS11_MC, vXS21_MC, vXS12_MC, vXS22_MC;
	double x, R, R_err, R_systerr, R_staterr,xs1, xs1_staterr,xs1_ltqeerr, xs1_systerr,xs2, xs2_staterr,xs2_ltqeerr, xs2_systerr,R_MC, xs1_mc, xs2_mc;
	TString dum;
	infile1 >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum>>dum >>dum >>dum;
	while(infile1 >> x >> R >> R_err >> R_staterr >> R_systerr >> xs1>> xs1_staterr>>xs1_ltqeerr>>xs1_systerr>>xs2>> xs2_staterr>>xs2_ltqeerr>>xs2_systerr>>R_MC>>xs1_mc>>xs2_mc){

		cerr<<Form("Kin5.0: x=%6.4f,  R = %6.4f, R_Err = %6.4f", x, R, R_err)<<endl;;
		vXbj1.push_back(x);
		vRatio_SystErr1.push_back(R_systerr);

		vXS11.push_back(xs1);
		vXS11_MC.push_back(xs1_mc);
		vXS11_StatErr.push_back(xs1_staterr);
		vXS11_SystErr.push_back(xs1_systerr);
		vXS11_LTQEErr.push_back(xs1_ltqeerr);
		vXS21.push_back(xs2);
		vXS21_MC.push_back(xs2_mc);
		vXS21_StatErr.push_back(xs2_staterr);
		vXS21_SystErr.push_back(xs2_systerr);
		vXS21_LTQEErr.push_back(xs2_ltqeerr);
	}
	infile1.close();

	infile2 >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum;
	while(infile2 >> x >> R >> R_err >> R_staterr >> R_systerr >> xs1>> xs1_staterr>>xs1_ltqeerr>>xs1_systerr>>xs2>> xs2_staterr>>xs2_ltqeerr>>xs2_systerr>>R_MC>>xs1_mc>>xs2_mc){
		cerr<<Form("Kin5.1: x=%6.4f,  R = %6.4f, R_Err = %6.4f", x, R, R_err)<<endl;;
		vXbj2.push_back(x);
		vRatio_SystErr2.push_back(R_systerr);

		vXS12.push_back(xs1);
		vXS12_MC.push_back(xs1_mc);
		vXS12_StatErr.push_back(xs1_staterr);
		vXS12_SystErr.push_back(xs1_systerr);
		vXS12_LTQEErr.push_back(xs1_ltqeerr);
		vXS22.push_back(xs2);
		vXS22_MC.push_back(xs2_mc);
		vXS22_StatErr.push_back(xs2_staterr);
		vXS22_SystErr.push_back(xs2_systerr);
		vXS22_LTQEErr.push_back(xs2_ltqeerr);
	}
	infile2.close();


	int Count=0;
	vector<double> vXbj, vR, vR_Err, vR_StatErr, vR_SystErr,vXS1, vXS1_StatErr, vXS1_LTQEErr,vXS1_SystErr, vXS2, vXS2_StatErr, vXS2_LTQEErr,vXS2_SystErr, vR_MC, vXS1_MC, vXS2_MC;
	Double_t x1,x2,ratio,err, syst_err, stat_err, ratio_mc;

	Double_t X_Min = 10, X_Max = -10, R_Min = 1000.0, R_Max = -1000.0;
	int J2 = -1;
	bool bFound = kFALSE;

        int J20= -1;
	bool bFirst = kTRUE;

        for(unsigned int i=0;i<vXbj1.size();i++){
		x1 = vXbj1[i];
		bFound = kFALSE;
		for(unsigned int j=0;j<vXbj2.size();j++){
			x2 = vXbj2[j];
                        /*Combine two bins{{{*/
                        if(x1>=0.5&&x2>=0.5&&abs(x1-x2)<0.0001){
                            if(bFirst){
                                bFirst = kFALSE;
                                J20 = j;
                            }

                            bFound = kTRUE;
                            J2 = j;
                            double xs1 = (vXS11[i] + vXS12[j])/2.0;
				double xs1_mc = (vXS11_MC[i] + vXS12_MC[j])/2.0;
				double xs1_stat_err = 1./sqrt( 1./pow(vXS11_StatErr[i],2) + 1./pow(vXS12_StatErr[j],2) );
				double xs1_syst_err = (vXS11_SystErr[i] + vXS12_SystErr[j])/2.0;
				double xs1_ltqe_err = (vXS11_LTQEErr[i] + vXS12_LTQEErr[j])/2.0;
				
				double xs2 = (vXS21[i] + vXS22[j])/2.0;
				double xs2_mc = (vXS21_MC[i] + vXS22_MC[j])/2.0;
				double xs2_stat_err = 1./sqrt( 1./pow(vXS21_StatErr[i],2) + 1./pow(vXS22_StatErr[j],2) );
				double xs2_syst_err = (vXS21_SystErr[i] + vXS22_SystErr[j])/2.0;
				double xs2_ltqe_err = (vXS21_LTQEErr[i] + vXS22_LTQEErr[j])/2.0;
				double ratio_syst_err = (vRatio_SystErr1[i]+vRatio_SystErr2[j])/2.0;

				ratio = factor00*xs1/xs2;
				ratio_mc = factor00*xs1_mc/xs2_mc;
				err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
				//actually stat_er5 includes both stat_err and LT_sys and Ne_sys
				stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
				syst_err =  ratio_syst_err;

				if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){/*{{{*/
					vXbj.push_back(x1);

					vXS1.push_back(xs1);
					vXS1_MC.push_back(xs1_mc);
					vXS1_StatErr.push_back(xs1_stat_err);
					vXS1_SystErr.push_back(xs1_syst_err);
					vXS1_LTQEErr.push_back(xs1_ltqe_err);
					
					vXS2.push_back(xs2);
					vXS2_MC.push_back(xs2_mc);
					vXS2_StatErr.push_back(xs2_stat_err);
					vXS2_SystErr.push_back(xs2_syst_err);
					vXS2_LTQEErr.push_back(xs2_ltqe_err);

					vR.push_back(ratio);
					vR_MC.push_back(ratio_mc);
					vR_Err.push_back(err);
					//vR_Err.push_back(ratio*stat_err);
					cerr <<Form("-----> 25^{#circ}: xbj1=%f, xbj2=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
							x1,x2,xs1,xs2,ratio, stat_err, syst_err)<<endl;

					if(R_Min > ratio)
						R_Min = ratio;
					if(R_Max < ratio)
						R_Max = ratio;
					if(X_Min > x1)
						X_Min = x1;
					if(X_Max < x1)
						X_Max = x1;
					Count++;
					outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
							x1,ratio,err, stat_err, syst_err, 
							xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
							xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err,ratio_mc, xs1_mc,xs2_mc )<<endl;
				}/*}}}*/
			}
			/*}}}*/
		}
		/*Don't fine the bin from the second set{{{*/	
		if(!(bFound)){
			x1 = vXbj1[i];
			double xs1 = vXS11[i];
			double xs1_mc = vXS11_MC[i];
			double xs1_stat_err = vXS11_StatErr[i];
			double xs1_syst_err = vXS11_SystErr[i];
			double xs1_ltqe_err = vXS11_LTQEErr[i];
			double xs2 = vXS21[i];
			double xs2_mc = vXS21_MC[i];
			double xs2_stat_err = pow(vXS21_StatErr[i],2);
			double xs2_syst_err = vXS21_SystErr[i];
			double xs2_ltqe_err = vXS21_LTQEErr[i];
			double ratio_syst_err = vRatio_SystErr1[i];

			ratio = factor00*xs1/xs2;
			ratio_mc = factor00*xs1_mc/xs2_mc;
			err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
			//actually stat_err includes both stat_err and LT_sys and Ne_sys
			stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
			syst_err =  ratio_syst_err;

			if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
				vXbj.push_back(x1);

				vXS1.push_back(xs1);
				vXS1_MC.push_back(xs1_mc);
				vXS1_StatErr.push_back(xs1_stat_err);
				vXS1_SystErr.push_back(xs1_syst_err);
				vXS1_LTQEErr.push_back(xs1_ltqe_err);
				vXS2.push_back(xs2);
				vXS2_MC.push_back(xs2_mc);
				vXS2_StatErr.push_back(xs2_stat_err);
				vXS2_SystErr.push_back(xs2_syst_err);
				vXS2_LTQEErr.push_back(xs2_ltqe_err);

				vR.push_back(ratio);
				vR_MC.push_back(ratio_mc);
				vR_Err.push_back(err);
				//vR_Err.push_back(ratio*stat_err);
				cerr <<Form("-----> Found one: xbj1=%f, xbj2=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
						x1,x2,xs1,xs2,ratio, stat_err, syst_err)<<endl;

				if(R_Min > ratio)
					R_Min = ratio;
				if(R_Max < ratio)
					R_Max = ratio;
				if(X_Min > x1)
					X_Min = x1;
				if(X_Max < x1)
					X_Max = x1;
				Count++;
				outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
						x1,ratio,err, stat_err, syst_err, 
						xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
						xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err,ratio_mc, xs1_mc,xs2_mc )<<endl;
			}
		}
		/*}}}*/
	}
	/*Pickup left over from the second set bin only{{{*/	
	for(unsigned int i=J2+1;i<vXbj2.size();i++){
		x1 = vXbj2[i];
		double xs1 = vXS12[i];
		double xs1_mc = vXS12_MC[i];
		double xs1_stat_err = vXS12_StatErr[i];
		double xs1_syst_err = vXS12_SystErr[i];
		double xs1_ltqe_err = vXS12_LTQEErr[i];
		double xs2 = vXS22[i];
		double xs2_mc = vXS22_MC[i];
		double xs2_stat_err = pow(vXS22_StatErr[i],2);
		double xs2_syst_err = vXS22_SystErr[i];
		double xs2_ltqe_err = vXS22_LTQEErr[i];
		double ratio_syst_err = vRatio_SystErr2[i];

		ratio = factor00*xs1/xs2;
		ratio_mc = factor00*xs1_mc/xs2_mc;
		err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
		//actually stat_err includes both stat_err and LT_sys and Ne_sys
		stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
		syst_err =  ratio_syst_err;

		if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
			vXbj.push_back(x1);

			vXS1.push_back(xs1);
			vXS1_MC.push_back(xs1_mc);
			vXS1_StatErr.push_back(xs1_stat_err);
			vXS1_SystErr.push_back(xs1_syst_err);
			vXS1_LTQEErr.push_back(xs1_ltqe_err);
			vXS2.push_back(xs2);
			vXS2_MC.push_back(xs2_mc);
			vXS2_StatErr.push_back(xs2_stat_err);
			vXS2_SystErr.push_back(xs2_syst_err);
			vXS2_LTQEErr.push_back(xs2_ltqe_err);

			vR.push_back(ratio);
			vR_MC.push_back(ratio_mc);
			vR_Err.push_back(err);
			//vR_Err.push_back(ratio*stat_err);
			cerr <<Form("-----> Found late one in 2325: xbj1=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
					x1,xs1,xs2,ratio, stat_err, syst_err)<<endl;

			if(R_Min > ratio)
				R_Min = ratio;
			if(R_Max < ratio)
				R_Max = ratio;
			if(X_Min > x1)
				X_Min = x1;
			if(X_Max < x1)
				X_Max = x1;
			Count++;
			outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
					x1,ratio,err, stat_err, syst_err, 
					xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
					xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err, ratio_mc, xs1_mc, xs2_mc )<<endl;
		}
	}
	/*}}}*/
	
        /*Pickup early left over from the second set bin only{{{*/	
        if(J20>=1){
            for(unsigned int i=0;i<J20;i++){
                x1 = vXbj2[i];
                double xs1 = vXS12[i];
                double xs1_mc = vXS12_MC[i];
                double xs1_stat_err = vXS12_StatErr[i];
                double xs1_syst_err = vXS12_SystErr[i];
                double xs1_ltqe_err = vXS12_LTQEErr[i];
                double xs2 = vXS22[i];
                double xs2_mc = vXS22_MC[i];
                double xs2_stat_err = pow(vXS22_StatErr[i],2);
                double xs2_syst_err = vXS22_SystErr[i];
                double xs2_ltqe_err = vXS22_LTQEErr[i];
                double ratio_syst_err = vRatio_SystErr2[i];

                ratio = factor00*xs1/xs2;
                ratio_mc = factor00*xs1_mc/xs2_mc;
                err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
                //actually stat_err includes both stat_err and LT_sys and Ne_sys
                stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
                syst_err =  ratio_syst_err;

                if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
                    vXbj.push_back(x1);

                    vXS1.push_back(xs1);
                    vXS1_MC.push_back(xs1_mc);
                    vXS1_StatErr.push_back(xs1_stat_err);
                    vXS1_SystErr.push_back(xs1_syst_err);
                    vXS1_LTQEErr.push_back(xs1_ltqe_err);
                    vXS2.push_back(xs2);
                    vXS2_MC.push_back(xs2_mc);
                    vXS2_StatErr.push_back(xs2_stat_err);
                    vXS2_SystErr.push_back(xs2_syst_err);
                    vXS2_LTQEErr.push_back(xs2_ltqe_err);

                    vR.push_back(ratio);
                    vR_MC.push_back(ratio_mc);
                    vR_Err.push_back(err);
                    //vR_Err.push_back(ratio*stat_err);
                    cerr <<Form("-----> Found early one in 2325: xbj1=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
                            x1,xs1,xs2,ratio, stat_err, syst_err)<<endl;

                    if(R_Min > ratio)
                        R_Min = ratio;
                    if(R_Max < ratio)
                        R_Max = ratio;
                    if(X_Min > x1)
                        X_Min = x1;
                    if(X_Max < x1)
                        X_Max = x1;
                    Count++;
                    outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
                            x1,ratio,err, stat_err, syst_err, 
                            xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
                            xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err, ratio_mc, xs1_mc, xs2_mc )<<endl;
                }
            }
        }
        /*}}}*/

	//Return the value
	for(int k=0; k<Count; k++){
		aXbj[k] = vXbj[k];
		aR_EX[k] = vR[k];
		aR_EX_Err[k] = vR_Err[k];
		aR_MC[k] = vR_MC[k];
	}
	aN[0] = Count;
	cerr<<"*****In Merge2325*** Factor = "<< factor00<<endl;
	outfile.close();
}
/*}}}*/

/*Merge212325{{{*/
void Merge212325(const TString& Target0, const TString& Target, double* aXbj, double* aR_EX, double* aR_EX_Err, double* aR_MC, int* aN){

	ofstream outfile(Form("./%s/XS_212325_%s_%s_%s_%s_Total.dat",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	ifstream infile1;
	infile1.open(Form("./%s/XS_2325_%s_%s_%s_%s_Total.dat",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	ifstream infile2;
    infile2.open(Form("./%s/XS_3.1_%s_%s_%s_%s.dat",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));

	outfile << Form("%7s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s", 
			"Xbj","Ratio","Ratio_TotalErr","Ratio_StatErr(rltv)","Ratio_SystErr(rltv)",
			"XS1","XS1_StatErr(rltv)","XS1_LTQEErr(rltv)","XS1_SystErr(rltv)",
			"XS2","XS2_StatErr(rltv)","XS2_LTQEErr(rltv)","XS2_SystErr(rltv)", "Ratio_MC", "XS1_MC", "XS2_MC" )<<endl;

	vector<double> vXbj1, vXS11,vRatio_SystErr1, vXS11_StatErr, vXS11_LTQEErr,vXS11_SystErr, vXS12, vXS21_StatErr, vXS21_LTQEErr,vXS21_SystErr;
	vector<double> vXbj2, vXS21,vRatio_SystErr2, vXS12_StatErr, vXS12_LTQEErr,vXS12_SystErr, vXS22, vXS22_StatErr, vXS22_LTQEErr,vXS22_SystErr;
	vector<double> vRatio_MC, vXS11_MC, vXS21_MC, vXS12_MC, vXS22_MC;
	double x, R, R_err, R_systerr, R_staterr,xs1, xs1_staterr,xs1_ltqeerr, xs1_systerr,xs2, xs2_staterr,xs2_ltqeerr, xs2_systerr,R_MC, xs1_mc, xs2_mc;
	TString dum;
	infile1 >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum>>dum >>dum >>dum;
	while(infile1 >> x >> R >> R_err >> R_staterr >> R_systerr >> xs1>> xs1_staterr>>xs1_ltqeerr>>xs1_systerr>>xs2>> xs2_staterr>>xs2_ltqeerr>>xs2_systerr>>R_MC>>xs1_mc>>xs2_mc){

		cerr<<Form("Kin2325: x=%6.4f,  R = %6.4f, R_Err = %6.4f", x, R, R_err)<<endl;;
		vXbj1.push_back(x);
		vRatio_SystErr1.push_back(R_systerr);

		vXS11.push_back(xs1);
		vXS11_MC.push_back(xs1_mc);
		vXS11_StatErr.push_back(xs1_staterr);
		vXS11_SystErr.push_back(xs1_systerr);
		vXS11_LTQEErr.push_back(xs1_ltqeerr);
		vXS21.push_back(xs2);
		vXS21_MC.push_back(xs2_mc);
		vXS21_StatErr.push_back(xs2_staterr);
		vXS21_SystErr.push_back(xs2_systerr);
		vXS21_LTQEErr.push_back(xs2_ltqeerr);
	}
	infile1.close();

	infile2 >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum >>dum;
	while(infile2 >> x >> R >> R_err >> R_staterr >> R_systerr >> xs1>> xs1_staterr>>xs1_ltqeerr>>xs1_systerr>>xs2>> xs2_staterr>>xs2_ltqeerr>>xs2_systerr>>R_MC>>xs1_mc>>xs2_mc){
		cerr<<Form("Kin5.1: x=%6.4f,  R = %6.4f, R_Err = %6.4f", x, R, R_err)<<endl;;
		vXbj2.push_back(x);
		vRatio_SystErr2.push_back(R_systerr);

		vXS12.push_back(xs1);
		vXS12_MC.push_back(xs1_mc);
		vXS12_StatErr.push_back(xs1_staterr);
		vXS12_SystErr.push_back(xs1_systerr);
		vXS12_LTQEErr.push_back(xs1_ltqeerr);
		vXS22.push_back(xs2);
		vXS22_MC.push_back(xs2_mc);
		vXS22_StatErr.push_back(xs2_staterr);
		vXS22_SystErr.push_back(xs2_systerr);
		vXS22_LTQEErr.push_back(xs2_ltqeerr);
	}
	infile2.close();

	int Count=0;
	vector<double> vXbj, vR, vR_Err, vR_StatErr, vR_SystErr,vXS1, vXS1_StatErr, vXS1_LTQEErr,vXS1_SystErr, vXS2, vXS2_StatErr, vXS2_LTQEErr,vXS2_SystErr, vR_MC, vXS1_MC, vXS2_MC;
	Double_t x1,x2,ratio,err, syst_err, stat_err, ratio_mc;

	Double_t X_Min = 10, X_Max = -10, R_Min = 1000.0, R_Max = -1000.0;
	int J2 = -1;
	bool bFound = kFALSE;
	
        bool bFirst = kTRUE;
	int J20= -1;
	for(unsigned int i=0;i<vXbj1.size();i++){
		x1 = vXbj1[i];
		bFound = kFALSE;
		for(unsigned int j=0;j<vXbj2.size();j++){
			x2 = vXbj2[j];
                        /*Combine two bins{{{*/
                        if(x1>=0.5&&x2>=0.5&&abs(x1-x2)<0.0001){
				if(bFirst){
                                    bFirst = kFALSE;
                                    J20 = j;//check which bin for the second target is found, pick up the early lefeover
                                }
				bFound = kTRUE;
                                J2 = j;
                                double xs1 = (vXS11[i] + vXS12[j])/2.0;
				double xs1_mc = (vXS11_MC[i] + vXS12_MC[j])/2.0;
				double xs1_stat_err = 1./sqrt( 1./pow(vXS11_StatErr[i],2) + 1./pow(vXS12_StatErr[j],2) );
				double xs1_syst_err = (vXS11_SystErr[i] + vXS12_SystErr[j])/2.0;
				double xs1_ltqe_err = (vXS11_LTQEErr[i] + vXS12_LTQEErr[j])/2.0;
				
				double xs2 = (vXS21[i] + vXS22[j])/2.0;
				double xs2_mc = (vXS21_MC[i] + vXS22_MC[j])/2.0;
				double xs2_stat_err = 1./sqrt( 1./pow(vXS21_StatErr[i],2) + 1./pow(vXS22_StatErr[j],2) );
				double xs2_syst_err = (vXS21_SystErr[i] + vXS22_SystErr[j])/2.0;
				double xs2_ltqe_err = (vXS21_LTQEErr[i] + vXS22_LTQEErr[j])/2.0;
				double ratio_syst_err = (vRatio_SystErr1[i]+vRatio_SystErr2[j])/2.0;

				ratio = factor00*xs1/xs2;
				ratio_mc = factor00*xs1_mc/xs2_mc;
				err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
				//actually stat_er5 includes both stat_err and LT_sys and Ne_sys
				stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
				syst_err =  ratio_syst_err;

				if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){/*{{{*/
					vXbj.push_back(x1);

					vXS1.push_back(xs1);
					vXS1_MC.push_back(xs1_mc);
					vXS1_StatErr.push_back(xs1_stat_err);
					vXS1_SystErr.push_back(xs1_syst_err);
					vXS1_LTQEErr.push_back(xs1_ltqe_err);
					
					vXS2.push_back(xs2);
					vXS2_MC.push_back(xs2_mc);
					vXS2_StatErr.push_back(xs2_stat_err);
					vXS2_SystErr.push_back(xs2_syst_err);
					vXS2_LTQEErr.push_back(xs2_ltqe_err);

					vR.push_back(ratio);
					vR_MC.push_back(ratio_mc);
					vR_Err.push_back(err);
					//vR_Err.push_back(ratio*stat_err);
					cerr <<Form("-----> 25^{#circ}: xbj1=%f, xbj2=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
							x1,x2,xs1,xs2,ratio, stat_err, syst_err)<<endl;

					if(R_Min > ratio)
						R_Min = ratio;
					if(R_Max < ratio)
						R_Max = ratio;
					if(X_Min > x1)
						X_Min = x1;
					if(X_Max < x1)
						X_Max = x1;
					Count++;
					outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
							x1,ratio,err, stat_err, syst_err, 
							xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
							xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err,ratio_mc, xs1_mc,xs2_mc )<<endl;
				}/*}}}*/
			}
			/*}}}*/
		}
		/*Don't fine the bin from the second set{{{*/	
		if(!(bFound)){
			x1 = vXbj1[i];
			double xs1 = vXS11[i];
			double xs1_mc = vXS11_MC[i];
			double xs1_stat_err = vXS11_StatErr[i];
			double xs1_syst_err = vXS11_SystErr[i];
			double xs1_ltqe_err = vXS11_LTQEErr[i];
			double xs2 = vXS21[i];
			double xs2_mc = vXS21_MC[i];
			double xs2_stat_err = pow(vXS21_StatErr[i],2);
			double xs2_syst_err = vXS21_SystErr[i];
			double xs2_ltqe_err = vXS21_LTQEErr[i];
			double ratio_syst_err = vRatio_SystErr1[i];

			ratio = factor00*xs1/xs2;
			ratio_mc = factor00*xs1_mc/xs2_mc;
			err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
			//actually stat_err includes both stat_err and LT_sys and Ne_sys
			stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
			syst_err =  ratio_syst_err;

			if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
				vXbj.push_back(x1);

				vXS1.push_back(xs1);
				vXS1_MC.push_back(xs1_mc);
				vXS1_StatErr.push_back(xs1_stat_err);
				vXS1_SystErr.push_back(xs1_syst_err);
				vXS1_LTQEErr.push_back(xs1_ltqe_err);
				vXS2.push_back(xs2);
				vXS2_MC.push_back(xs2_mc);
				vXS2_StatErr.push_back(xs2_stat_err);
				vXS2_SystErr.push_back(xs2_syst_err);
				vXS2_LTQEErr.push_back(xs2_ltqe_err);

				vR.push_back(ratio);
				vR_MC.push_back(ratio_mc);
				vR_Err.push_back(err);
                                //vR_Err.push_back(ratio*stat_err);
                                cerr <<Form("-----> Found one: xbj1=%f, xbj2=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
						x1,x2,xs1,xs2,ratio, stat_err, syst_err)<<endl;

				if(R_Min > ratio)
					R_Min = ratio;
				if(R_Max < ratio)
					R_Max = ratio;
				if(X_Min > x1)
					X_Min = x1;
				if(X_Max < x1)
					X_Max = x1;
				Count++;
				outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
						x1,ratio,err, stat_err, syst_err, 
						xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
						xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err,ratio_mc, xs1_mc,xs2_mc )<<endl;
			}
		}
		/*}}}*/
	}
	/*Pickup late left over from the second set bin only{{{*/	
	for(unsigned int i=J2+1;i<vXbj2.size();i++){
		x1 = vXbj2[i];
		double xs1 = vXS12[i];
		double xs1_mc = vXS12_MC[i];
		double xs1_stat_err = vXS12_StatErr[i];
		double xs1_syst_err = vXS12_SystErr[i];
		double xs1_ltqe_err = vXS12_LTQEErr[i];
		double xs2 = vXS22[i];
		double xs2_mc = vXS22_MC[i];
		double xs2_stat_err = pow(vXS22_StatErr[i],2);
		double xs2_syst_err = vXS22_SystErr[i];
		double xs2_ltqe_err = vXS22_LTQEErr[i];
		double ratio_syst_err = vRatio_SystErr2[i];

		ratio = factor00*xs1/xs2;
		ratio_mc = factor00*xs1_mc/xs2_mc;
		err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
		//actually stat_err includes both stat_err and LT_sys and Ne_sys
		stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
		syst_err =  ratio_syst_err;

		if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
			vXbj.push_back(x1);

			vXS1.push_back(xs1);
			vXS1_MC.push_back(xs1_mc);
			vXS1_StatErr.push_back(xs1_stat_err);
			vXS1_SystErr.push_back(xs1_syst_err);
			vXS1_LTQEErr.push_back(xs1_ltqe_err);
			vXS2.push_back(xs2);
			vXS2_MC.push_back(xs2_mc);
			vXS2_StatErr.push_back(xs2_stat_err);
			vXS2_SystErr.push_back(xs2_syst_err);
			vXS2_LTQEErr.push_back(xs2_ltqe_err);

			vR.push_back(ratio);
			vR_MC.push_back(ratio_mc);
			vR_Err.push_back(err);
                        //vR_Err.push_back(ratio*stat_err);
                        cerr <<Form("-----> Found one late 212325: xbj1=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
					x1,xs1,xs2,ratio, stat_err, syst_err)<<endl;

			if(R_Min > ratio)
				R_Min = ratio;
			if(R_Max < ratio)
				R_Max = ratio;
			if(X_Min > x1)
				X_Min = x1;
			if(X_Max < x1)
				X_Max = x1;
			Count++;
			outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
					x1,ratio,err, stat_err, syst_err, 
					xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
					xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err, ratio_mc, xs1_mc, xs2_mc )<<endl;
		}
	}
	/*}}}*/
	
        /*Pickup early left over from the second set bin only{{{*/	
        if(J20>=1){
            for(unsigned int i=0;i<J20; i++){
                x1 = vXbj2[i];
                double xs1 = vXS12[i];
                double xs1_mc = vXS12_MC[i];
                double xs1_stat_err = vXS12_StatErr[i];
                double xs1_syst_err = vXS12_SystErr[i];
                double xs1_ltqe_err = vXS12_LTQEErr[i];
                double xs2 = vXS22[i];
                double xs2_mc = vXS22_MC[i];
                double xs2_stat_err = pow(vXS22_StatErr[i],2);
                double xs2_syst_err = vXS22_SystErr[i];
                double xs2_ltqe_err = vXS22_LTQEErr[i];
                double ratio_syst_err = vRatio_SystErr2[i];

                ratio = factor00*xs1/xs2;
                ratio_mc = factor00*xs1_mc/xs2_mc;
                err = ratio * sqrt( pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2) + pow(ratio_syst_err,2) );
                //actually stat_err includes both stat_err and LT_sys and Ne_sys
                stat_err = sqrt(pow( xs1_stat_err,2) + pow( xs2_stat_err,2) + pow( xs1_ltqe_err,2) + pow( xs2_ltqe_err,2));
                syst_err =  ratio_syst_err;

                if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
                    vXbj.push_back(x1);

                    vXS1.push_back(xs1);
                    vXS1_MC.push_back(xs1_mc);
                    vXS1_StatErr.push_back(xs1_stat_err);
                    vXS1_SystErr.push_back(xs1_syst_err);
                    vXS1_LTQEErr.push_back(xs1_ltqe_err);
                    vXS2.push_back(xs2);
                    vXS2_MC.push_back(xs2_mc);
                    vXS2_StatErr.push_back(xs2_stat_err);
                    vXS2_SystErr.push_back(xs2_syst_err);
                    vXS2_LTQEErr.push_back(xs2_ltqe_err);

                    vR.push_back(ratio);
                    vR_MC.push_back(ratio_mc);
                    vR_Err.push_back(err);
                    //vR_Err.push_back(ratio*stat_err);
                    cerr <<Form("-----> Found one early 212325: xbj1=%f, XS1=%f, XS2=%f,Ratio=%f, (stat_err=%e, syst_err=%e) ",
                            x1,xs1,xs2,ratio, stat_err, syst_err)<<endl;

                    if(R_Min > ratio)
                        R_Min = ratio;
                    if(R_Max < ratio)
                        R_Max = ratio;
                    if(X_Min > x1)
                        X_Min = x1;
                    if(X_Max < x1)
                        X_Max = x1;
                    Count++;
                    outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
                            x1,ratio,err, stat_err, syst_err, 
                            xs1, xs1_stat_err, xs1_ltqe_err, xs1_syst_err,
                            xs2, xs2_stat_err, xs2_ltqe_err, xs2_syst_err, ratio_mc, xs1_mc, xs2_mc )<<endl;
                }
            }
        }
        /*}}}*/

	//Return the value
	for(int k=0; k<Count; k++){
		aXbj[k] = vXbj[k];
		aR_EX[k] = vR[k];
		aR_EX_Err[k] = vR_Err[k];
		aR_MC[k] = vR_MC[k];
	}
	aN[0] = Count;
	cerr<<"*****In Merge212325*** Factor = "<< factor00<<endl;
	outfile.close();
}
/*}}}*/



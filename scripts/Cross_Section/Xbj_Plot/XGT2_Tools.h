//const double He4_Norm =1.0/0.864;
//const double He4_Norm =10./8.0;
const double He4_Norm =1.;
//const double He3_Norm =10./8.0;
const double He3_Norm =1.;
const double He4_MC_Norm =0.80;
//const double He4_MC_Norm =1.00;
const double He3_MC_Norm =1.00;
TString OutFile_Dir = "./new_both/";
double factor00=0;
TString Target0,Target,Com0,Com;
const TString aInputFilePath = "/work/halla/e08014/disk1/yez/Xbj_Cross_Section/results/Ratio/";
/*List the Statistical Errors{{{*//*{{{*/
//all values are relative errors
/*Common{{{*/
const double SystErr_Nmc_Foil = 1./sqrt(5000000.);
const double SystErr_Nmc_Cryo = 1./sqrt(20000000.);

const double SystErr_HRS_Angle = 0.5*1e-3;//0.5mrad resolution
const double SystErr_HRS_Mom = 0.0002;//0.02%
const double SystErr_Beam_Energy = 0.0005;//0.05%
//const double SystErr_Beam_Charge = 0.01;//calculate on the fly
//const double SystErr_LiveTime = 0.01;//<calculate on the fly

const double SystErr_Rho_H2 = 0.0008/3.3506; // need updated
const double SystErr_Rho_He3 = 0.0008/0.66068; // need updated
const double SystErr_Rho_He4 = 0.0008/0.6652; // need updated
const double SystErr_Rho_C12 = 0.0008/0.8918; // delta_rho/rho
const double SystErr_Rho_Ca40= 0.01/0.8990; // need updated
const double SystErr_Rho_Ca48= 0.01/0.8190; // need updated

const double SystErr_Boil_H2 = 0.05; //5%, need updated
const double SystErr_Boil_He3 = 0.05; //5%, need updated
const double SystErr_Boil_He4 = 0.05; //5%, need updated

const double SystErr_Dummy_H2 = 0.01; //1%, need updated
const double SystErr_Dummy_He3 = 0.01; //1%, need updated
const double SystErr_Dummy_He4 = 0.01; //1%, need updated
/*}}}*/

/*Corrections{{{*/
const double SystErr_RadC_H2 = 0.01; //1%
const double SystErr_RadC_He3 = 0.01; //1%
const double SystErr_RadC_He4 = 0.01; //1%
const double SystErr_RadC_C12 = 0.01; //1%
const double SystErr_RadC_Ca40 = 0.01; //1%
const double SystErr_RadC_Ca48 = 0.01; //1%

const double SystErr_CouC_H2 = 0.01; //1%
const double SystErr_CouC_He3 = 0.01; //1%
const double SystErr_CouC_He4 = 0.01; //1%
const double SystErr_CouC_C12 = 0.01; //1%
const double SystErr_CouC_Ca40 = 0.01; //1%
const double SystErr_CouC_Ca48 = 0.01; //1%

const double SystErr_AccC_H2 = 0.01; //1%
const double SystErr_AccC_He3 = 0.01; //1%
const double SystErr_AccC_He4 = 0.01; //1%
const double SystErr_AccC_C12 = 0.01; //1%
const double SystErr_AccC_Ca40 = 0.01; //1%
const double SystErr_AccC_Ca48 = 0.01; //1%

const double SystErr_BinC_H2 = 0.01; //1%
const double SystErr_BinC_He3 = 0.01; //1%
const double SystErr_BinC_He4 = 0.01; //1%
const double SystErr_BinC_C12 = 0.01; //1%
const double SystErr_BinC_Ca40 = 0.01; //1%
const double SystErr_BinC_Ca48 = 0.01; //1%
/*}}}*/

/*Efficiencies{{{*/
const double SystErr_Trig_Eff_H2 = 0.01; //1%
const double SystErr_Trig_Eff_He3 = 0.01; //1%
const double SystErr_Trig_Eff_He4 = 0.01; //1%
const double SystErr_Trig_Eff_C12 = 0.01; //1%
const double SystErr_Trig_Eff_Ca40 = 0.01; //1%
const double SystErr_Trig_Eff_Ca48 = 0.01; //1%

const double SystErr_Trac_Eff_H2 = 0.01; //1%
const double SystErr_Trac_Eff_He3 = 0.01; //1%
const double SystErr_Trac_Eff_He4 = 0.01; //1%
const double SystErr_Trac_Eff_C12 = 0.01; //1%
const double SystErr_Trac_Eff_Ca40 = 0.01; //1%
const double SystErr_Trac_Eff_Ca48 = 0.01; //1%

const double SystErr_Calo_Eff_H2 = 0.01; //1%
const double SystErr_Calo_Eff_He3 = 0.01; //1%
const double SystErr_Calo_Eff_He4 = 0.01; //1%
const double SystErr_Calo_Eff_C12 = 0.01; //1%
const double SystErr_Calo_Eff_Ca40 = 0.01; //1%
const double SystErr_Calo_Eff_Ca48 = 0.01; //1%

const double SystErr_Cher_Eff_H2 = 0.01; //1%
const double SystErr_Cher_Eff_He3 = 0.01; //1%
const double SystErr_Cher_Eff_He4 = 0.01; //1%
const double SystErr_Cher_Eff_C12 = 0.01; //1%
const double SystErr_Cher_Eff_Ca40 = 0.01; //1%
const double SystErr_Cher_Eff_Ca48 = 0.01; //1%

const double SystErr_PID_Eff_H2 = 0.01; //1%
const double SystErr_PID_Eff_He3 = 0.01; //1%
const double SystErr_PID_Eff_He4 = 0.01; //1%
const double SystErr_PID_Eff_C12 = 0.01; //1%
const double SystErr_PID_Eff_Ca40 = 0.01; //1%
const double SystErr_PID_Eff_Ca48 = 0.01; //1%
/*}}}*/
/*}}}*//*}}}*/

/*inline double gGet_Total_SystErr(const TString& aTarget_Name, const TString& aArm, const double aTheta){{{*/
inline double gGet_Total_SystErr(const TString& aTarget_Name, const TString& aArm, const double aTheta){
	double total_err = 0.0;

	total_err += pow(SystErr_HRS_Angle/(aTheta*3.1415926/180.0),2); 
	total_err += pow(SystErr_HRS_Mom,2); 
	total_err += pow(SystErr_Beam_Energy,2); 

	if(aTarget_Name=="H2"||aTarget_Name=="He3"||aTarget_Name=="He4")
		total_err += pow( SystErr_Nmc_Cryo,2); 
	else
		total_err += pow( SystErr_Nmc_Foil,2); 

	/*H2{{{*/
	if(aTarget_Name=="H2"){
		//Target density related
		total_err += pow(SystErr_Boil_H2, 2); 
		total_err += pow(SystErr_Rho_H2, 2); 
		total_err += pow(SystErr_Dummy_H2, 2); 
		//corrections
		total_err += pow(SystErr_RadC_H2, 2); 
		total_err += pow(SystErr_CouC_H2, 2); 
		total_err += pow(SystErr_AccC_H2, 2); 
		total_err += pow(SystErr_BinC_H2, 2); 
		//efficiencies
		total_err += pow(SystErr_Trig_Eff_H2, 2); 
		total_err += pow(SystErr_Trac_Eff_H2, 2); 
		total_err += pow(SystErr_Calo_Eff_H2, 2); 
		total_err += pow(SystErr_Cher_Eff_H2, 2); 
		total_err += pow(SystErr_PID_Eff_H2, 2); 
	}/*}}}*/
	/*He3{{{*/
	if(aTarget_Name=="He3"){
		//Target density related
		total_err += pow(SystErr_Boil_He3, 2); 
		total_err += pow(SystErr_Rho_He3, 2); 
		total_err += pow(SystErr_Dummy_He3, 2); 
		//corrections
		total_err += pow(SystErr_RadC_He3, 2); 
		total_err += pow(SystErr_CouC_He3, 2); 
		total_err += pow(SystErr_AccC_He3, 2); 
		total_err += pow(SystErr_BinC_He3, 2); 
		//efficiencies
		total_err += pow(SystErr_Trig_Eff_He3, 2); 
		total_err += pow(SystErr_Trac_Eff_He3, 2); 
		total_err += pow(SystErr_Calo_Eff_He3, 2); 
		total_err += pow(SystErr_Cher_Eff_He3, 2); 
		total_err += pow(SystErr_PID_Eff_He3, 2); 
	}/*}}}*/
	/*He4{{{*/
	else if(aTarget_Name=="He4"){
		//Target density related
		total_err += pow(SystErr_Boil_He4, 2); 
		total_err += pow(SystErr_Rho_He4, 2); 
		total_err += pow(SystErr_Dummy_He4, 2); 
		//corrections
		total_err += pow(SystErr_RadC_He4, 2); 
		total_err += pow(SystErr_CouC_He4, 2); 
		total_err += pow(SystErr_AccC_He4, 2); 
		total_err += pow(SystErr_BinC_He4, 2); 
		//efficiencies
		total_err += pow(SystErr_Trig_Eff_He4, 2); 
		total_err += pow(SystErr_Trac_Eff_He4, 2); 
		total_err += pow(SystErr_Calo_Eff_He4, 2); 
		total_err += pow(SystErr_Cher_Eff_He4, 2); 
		total_err += pow(SystErr_PID_Eff_He4, 2); 
	}/*}}}*/
	/*C12{{{*/
	else if(aTarget_Name=="C12"){
		//Target density related
		total_err += pow(SystErr_Rho_C12, 2); 
		//corrections
		total_err += pow(SystErr_RadC_C12, 2); 
		total_err += pow(SystErr_CouC_C12, 2); 
		total_err += pow(SystErr_AccC_C12, 2); 
		total_err += pow(SystErr_BinC_C12, 2); 
		//efficiencies
		total_err += pow(SystErr_Trig_Eff_C12, 2); 
		total_err += pow(SystErr_Trac_Eff_C12, 2); 
		total_err += pow(SystErr_Calo_Eff_C12, 2); 
		total_err += pow(SystErr_Cher_Eff_C12, 2); 
		total_err += pow(SystErr_PID_Eff_C12, 2); 
	}/*}}}*/
	/*Ca40{{{*/
	else if(aTarget_Name=="Ca40"){
		//Target density related
		total_err += pow(SystErr_Rho_Ca40, 2); 
		//corrections
		total_err += pow(SystErr_RadC_Ca40, 2); 
		total_err += pow(SystErr_CouC_Ca40, 2); 
		total_err += pow(SystErr_AccC_Ca40, 2); 
		total_err += pow(SystErr_BinC_Ca40, 2); 
		//efficiencies
		total_err += pow(SystErr_Trig_Eff_Ca40, 2); 
		total_err += pow(SystErr_Trac_Eff_Ca40, 2); 
		total_err += pow(SystErr_Calo_Eff_Ca40, 2); 
		total_err += pow(SystErr_Cher_Eff_Ca40, 2); 
		total_err += pow(SystErr_PID_Eff_Ca40, 2); 
	}/*}}}*/
	/*Ca48{{{*/
	else if(aTarget_Name=="Ca48"){
		//Target density related
		total_err += pow(SystErr_Rho_Ca48, 2); 
		//corrections
		total_err += pow(SystErr_RadC_Ca48, 2); 
		total_err += pow(SystErr_CouC_Ca48, 2); 
		total_err += pow(SystErr_AccC_Ca48, 2); 
		total_err += pow(SystErr_BinC_Ca48, 2); 
		//efficiencies
		total_err += pow(SystErr_Trig_Eff_Ca48, 2); 
		total_err += pow(SystErr_Trac_Eff_Ca48, 2); 
		total_err += pow(SystErr_Calo_Eff_Ca48, 2); 
		total_err += pow(SystErr_Cher_Eff_Ca48, 2); 
		total_err += pow(SystErr_PID_Eff_Ca48, 2); 
	} /*}}}*/

	return sqrt(total_err);//return a relative total systematic error
	//return 0.0;//return a relative total systematic error
} 
/*}}}*/

/*inline double gGet_Ratio_SystErr(const TString& aTarget_Name1, const TString& aTarget_Name2, const TString& aArm, const double aTheta){{{*/
inline double gGet_Ratio_SystErr(const TString& aTarget_Name1, const TString& aTarget_Name2){
	double h2_err = 0;
	h2_err += pow( SystErr_Nmc_Cryo,2); 
	h2_err += pow( SystErr_Trig_Eff_H2,2); 
	h2_err += pow( SystErr_Rho_H2,2); 
	h2_err += pow( SystErr_Boil_H2,2); 
	h2_err += pow( SystErr_Dummy_H2,2); 
	h2_err += pow( SystErr_RadC_H2,2); 
	h2_err += pow( SystErr_CouC_H2,2); 
	h2_err += pow( SystErr_AccC_H2,2); 
	double he3_err = 0;
	he3_err += pow( SystErr_Nmc_Cryo,2); 
	he3_err += pow( SystErr_Trig_Eff_He3,2); 
	he3_err += pow( SystErr_Rho_He3,2); 
	he3_err += pow( SystErr_Boil_He3,2); 
	he3_err += pow( SystErr_Dummy_He3,2); 
	he3_err += pow( SystErr_RadC_He3,2); 
	he3_err += pow( SystErr_CouC_He3,2); 
	he3_err += pow( SystErr_AccC_He3,2); 
	double he4_err = 0;
	he4_err += pow( SystErr_Nmc_Cryo,2); 
	he4_err += pow( SystErr_Trig_Eff_He4,2); 
	he4_err += pow( SystErr_Rho_He4,2); 
	he4_err += pow( SystErr_Boil_He4,2); 
	he4_err += pow( SystErr_Dummy_He4,2); 
	he4_err += pow( SystErr_RadC_He4,2); 
	he4_err += pow( SystErr_CouC_He4,2); 
	he4_err += pow( SystErr_AccC_He4,2); 
	double c12_err = 0;
	c12_err += pow( SystErr_Nmc_Foil,2); 
	c12_err += pow( SystErr_Trig_Eff_C12,2); 
	c12_err += pow( SystErr_Rho_C12,2); 
	c12_err += pow( SystErr_RadC_C12,2); 
	c12_err += pow( SystErr_CouC_C12,2); 
	c12_err += pow( SystErr_AccC_C12,2); 
	double ca40_err = 0;
	ca40_err += pow( SystErr_Nmc_Foil,2); 
	ca40_err += pow( SystErr_Trig_Eff_Ca40,2); 
	ca40_err += pow( SystErr_Rho_Ca40,2); 
	ca40_err += pow( SystErr_RadC_Ca40,2); 
	ca40_err += pow( SystErr_CouC_Ca40,2); 
	ca40_err += pow( SystErr_AccC_Ca40,2); 
	double ca48_err = 0;
	ca48_err += pow( SystErr_Nmc_Foil,2); 
	ca48_err += pow( SystErr_Trig_Eff_Ca48,2); 
	ca48_err += pow( SystErr_Rho_Ca48,2); 
	ca48_err += pow( SystErr_RadC_Ca48,2); 
	ca48_err += pow( SystErr_CouC_Ca48,2); 
	ca48_err += pow( SystErr_AccC_Ca48,2); 

	double ratio_err = 0.0;
	if(aTarget_Name1 == "H2")
		ratio_err += h2_err;
	else if(aTarget_Name1 == "He3")
		ratio_err += he3_err;
	else if(aTarget_Name1 == "He4")
		ratio_err += he4_err;
	else if(aTarget_Name1 == "C12")
		ratio_err += c12_err;
	else if(aTarget_Name1 == "Ca40")
		ratio_err += ca40_err;
	else if(aTarget_Name1 == "Ca48")
		ratio_err += ca40_err;

	if(aTarget_Name2 == "H2")
		ratio_err += h2_err;
	else if(aTarget_Name2 == "He3")
		ratio_err += he3_err;
	else if(aTarget_Name2 == "He4")
		ratio_err += he4_err;
	else if(aTarget_Name2 == "C12")
		ratio_err += c12_err;
	else if(aTarget_Name2 == "Ca40")
		ratio_err += ca40_err;
	else if(aTarget_Name2 == "Ca48")
		ratio_err += ca40_err;

	if(aTarget_Name1 == "He4" && aTarget_Name2 == "He3")
            ratio_err -= pow( SystErr_Boil_He3,2);//give 5% for the ratio of two cryo-gen target
        if(aTarget_Name1 == "He4" && aTarget_Name2 == "H2")
            ratio_err -= pow( SystErr_Boil_He3,2);//give 5% for the ratio
        if(aTarget_Name1 == "He3" && aTarget_Name2 == "H2")
            ratio_err -= pow( SystErr_Boil_He3,2);//give 5% for the ratio

        if(aTarget_Name2 == "He4" && aTarget_Name1 == "He3")
            ratio_err -= pow( SystErr_Boil_He3,2);//give 5% for the ratio of two cryo-gen target
        if(aTarget_Name2 == "He4" && aTarget_Name1 == "H2")
            ratio_err -= pow( SystErr_Boil_He3,2);//give 5% for the ratio
        if(aTarget_Name2 == "He3" && aTarget_Name1 == "H2")
            ratio_err -= pow( SystErr_Boil_He3,2);//give 5% for the ratio


        return sqrt(ratio_err); //return relative ratio error
}
/*}}}*/

/*Get_Target_Name{{{*/
TString gGet_Target_Name(const TString& aName){
	TString aTarget_Name="MM";

	if(aName.Contains("H2")||aName.Contains("D2"))
		aTarget_Name="H2";
	else if(aName.Contains("He3"))
		aTarget_Name="He3";
	else if(aName.Contains("He4"))
		aTarget_Name="He4";
	else if(aName.Contains("C12"))
		aTarget_Name="C12";
	else if(aName.Contains("Ca40"))
		aTarget_Name="Ca40";
	else if(aName.Contains("Ca48"))
		aTarget_Name="Ca48";
	else
		cerr<<"*** I don't know the target name!!!"<<endl;
	return aTarget_Name;
}
/*}}}*/

/*Get_Kin_Name{{{*/
TString gGet_Kin_Name(const TString& aKin){
	TString aKin_Name="MM";
	if(aKin.Contains("3.1"))
		aKin_Name="3.1";
	else if(aKin.Contains("3.2"))
		aKin_Name="3.2";
	else if(aKin.Contains("4.1"))
		aKin_Name="4.1";
	else if(aKin.Contains("4.2"))
		aKin_Name="4.2";
	else if(aKin.Contains("5.0") && !aKin.Contains("5.05"))
		aKin_Name="5.0";
	else if(aKin.Contains("5.05"))
		aKin_Name="5.05";
	else if(aKin.Contains("5.1"))
		aKin_Name="5.1";
	else if(aKin.Contains("5.2"))
		aKin_Name="5.2";
	else if(aKin.Contains("6.5"))
		aKin_Name="6.5";
	else
		cerr<<"*** I don't know the kinematics name!!!"<<endl;
	return aKin_Name;
}
/*}}}*/

TString Get_Target_Label(const TString target_name){/*{{{*/
    TString ltarget=target_name;

    if(target_name =="H2"||target_name=="D2")
         ltarget="^{2}H";
    else if(target_name =="He3")
         ltarget="^{3}He";
    else if(target_name =="He4")
         ltarget="^{4}He";
    else if(target_name =="C12")
         ltarget="^{12}C";
    else if(target_name =="Ca40")
         ltarget="^{40}Ca";
    else if(target_name =="Ca48")
        ltarget="^{48}Ca";
 else if(target_name =="Al27")
         ltarget="^{27}Al";
 else 
    cerr<<"***, Unknown target name in Get_Target_Label()"<<endl;

 return ltarget;
}/*}}}*/

/*Cuts on the edge of Xbj{{{*/
// Cut_L_Min Cut_L_Max Cut_R_Min Cut_R_Max
const double E0 = 3.356;

//const double Xbj_Cut_21_1[4] = {1.25, 2.15,1.25,2.15}; 
//const double Xbj_Cut_21_2[4] = {1.65, 3.10,1.65,3.10}; 
//const double Xbj_Cut_23_1[4] = {1.30, 2.15,1.30,2.15}; 
//const double Xbj_Cut_23_2[4] = {1.85, 3.10,1.85,3.10};
//const double Xbj_Cut_QE_1[4] = {0.75, 1.20,0.75,1.20}; 
//const double Xbj_Cut_QE_2[4] = {1.05, 1.55,1.05,1.55}; 
//const double Xbj_Cut_25_1[4] = {1.35, 2.10,1.35,2.10};
//const double Xbj_Cut_25_2[4] = {2.00, 3.10,2.00,3.10}; 
//const double Xbj_Cut_28_1[4] = {1.80, 3.10,1.80,3.10};

const double Xbj_Cut_21_1[4] = {1.25, 2.15,1.25,2.15}; 
const double Xbj_Cut_21_2[4] = {1.65, 2.80,1.65,2.80}; 
const double Xbj_Cut_23_1[4] = {1.30, 2.15,1.30,2.15}; 
const double Xbj_Cut_23_2[4] = {1.85, 2.90,1.85,2.90};
const double Xbj_Cut_QE_1[4] = {0.75, 1.20,0.75,1.20}; 
const double Xbj_Cut_QE_2[4] = {1.05, 1.55,1.05,1.55}; 
const double Xbj_Cut_25_1[4] = {1.35, 2.10,1.35,2.10};
const double Xbj_Cut_25_2[4] = {2.00, 2.90,2.00,2.90}; 
const double Xbj_Cut_28_1[4] = {1.80, 4.90,1.80,2.90}; 
/*
   const double Xbj_Cut_21_1[4] = {1.25, 1.75,1.25,1.75}; 
   const double Xbj_Cut_21_2[4] = {2.10, 3.00,2.10,3.00}; 
   const double Xbj_Cut_23_1[4] = {1.45, 2.05,1.45,2.05}; 
   const double Xbj_Cut_23_2[4] = {1.95, 3.00,1.95,3.00};
   const double Xbj_Cut_QE_1[4] = {0.85, 1.15,0.85,1.15}; 
   const double Xbj_Cut_QE_2[4] = {1.05, 1.50,1.05,1.50}; 
   const double Xbj_Cut_25_1[4] = {1.40, 2.10,1.40,2.10};
   const double Xbj_Cut_25_2[4] = {2.10, 3.00,2.10,3.00}; 
   const double Xbj_Cut_28_1[4] = {1.90, 3.00,1.90,3.00}; 
   */
double Ep_Cut_21_1[4] = {2.80, 3.00,2.80,3.00}; 
double Ep_Cut_21_2[4] = {2.94, 3.18,2.94,3.18}; 
double Ep_Cut_23_1[4] = {2.74, 2.94,2.74,2.94}; 
double Ep_Cut_23_2[4] = {2.92, 3.16,2.92,3.16};
double Ep_Cut_QE_1[4] = {2.42, 2.58,2.42,2.58}; 
double Ep_Cut_QE_2[4] = {2.56, 2.74,2.56,2.74}; 
double Ep_Cut_25_1[4] = {2.70, 2.88,2.70,2.88};
double Ep_Cut_25_2[4] = {2.88, 3.12,2.88,3.12}; 
double Ep_Cut_28_1[4] = {2.74, 2.98,2.74,2.98};

inline void gGet_Ep_Edge(const TString& aTarget){

    TARGET_MASS_A = gGet_Target_Mass_A(aTarget.Data());

	double Theta = 0.0, SinSQ = 0.0;
	for(int i=0;i<4;i++){
		Theta = 21.00;
		SinSQ = pow(sin(Theta*TMath::DegToRad()/2.0),2); //Define Sin(Theta/2.)^2
		Ep_Cut_21_1[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*TARGET_MASS_A*Xbj_Cut_21_1[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Ep_Cut_21_2[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*TARGET_MASS_A*Xbj_Cut_21_2[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Theta = 23.00;
		SinSQ = pow(sin(Theta*TMath::DegToRad()/2.0),2); //Define Sin(Theta/2.)^2
		Ep_Cut_23_1[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*TARGET_MASS_A*Xbj_Cut_23_1[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Ep_Cut_23_2[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*TARGET_MASS_A*Xbj_Cut_23_2[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Theta = 25.00;
		SinSQ = pow(sin(Theta*TMath::DegToRad()/2.0),2); //Define Sin(Theta/2.)^2
		Ep_Cut_QE_1[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*TARGET_MASS_A*Xbj_Cut_QE_1[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Ep_Cut_QE_2[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*TARGET_MASS_A*Xbj_Cut_QE_2[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Ep_Cut_25_1[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*TARGET_MASS_A*Xbj_Cut_25_1[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Ep_Cut_25_2[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*TARGET_MASS_A*Xbj_Cut_25_2[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Theta = 28.00;
		SinSQ = pow(sin(Theta*TMath::DegToRad()/2.0),2); //Define Sin(Theta/2.)^2
		Ep_Cut_28_1[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*TARGET_MASS_A*Xbj_Cut_28_1[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
	}
}
/*}}}*/

/*Get He3 RadCorr{{{*/
inline double gGet_RadCorr_He3(const double aXbj){
	double aRadCor = 1-0.1*(aXbj-2.45)+0.025*pow((aXbj-2.45),2)-0.72*pow((aXbj-2.45),3);
	//return 1.0/aRadCor;
	return 1.0;
}
/*}}}*/

/*E02-019 Data{{{*/
void E02019(const TString& aInputFileName, const double aTheta,double* aXbj, double* aR_EX, double* aR_EX_Err, int* aN){
	int aline = 0;

	ofstream outfile(Form("./%s/E02019_XS_%s_%s.dat",OutFile_Dir.Data(), Target0.Data(),Target.Data()));
	outfile << Form("%7s %14s %14s %14s %14s %14s %14s", "Xbj","Ratio","XS1","XS2","Ratio_Err","XS_Err1","XS_Err2" )<<endl;

	const TString aName_T1 = gGet_InputFile_Var(aInputFileName, aline); aline++;
	const TString aName_T2 = gGet_InputFile_Var(aInputFileName, aline); aline++;
	const double factor = gGet_InputFile_Var(aInputFileName, aline).Atof(); 
	cerr<<Form("==== Reading E02-019 Data from %s and %s ", aName_T1.Data(), aName_T2.Data())<<endl;

	TString Ascii_File1 = Form("%s/e02019/%s",aInputFilePath.Data(),aName_T1.Data());
	cerr<<Form(" === Reading E02019 data from %s", Ascii_File1.Data())<<endl;
	ifstream infile1(Ascii_File1);
	TString Ascii_File2 = Form("%s/e02019/%s",aInputFilePath.Data(),aName_T2.Data());
	cerr<<Form(" === Reading E02019 data from %s", Ascii_File2.Data())<<endl;
	ifstream infile2(Ascii_File2);

	Double_t xbj, Q2, nA, nTheta, nP0, nEp, nXS_Rad, nXS_Born,nXS_CC,nFrac_Err;  
	const double nE0 = 5.776;
	/*First Target:{{{*/
	vector<double> vXbj1, vXS1, vXS_Err1,vP1,vTheta1;
	int N1=0;
	while(!(infile1.eof())){
		infile1 >> nA >> nTheta >> nP0 >> nEp >> nXS_Rad >> nXS_Born >> nXS_CC >> nFrac_Err;
		if(abs(nTheta-aTheta)<1.0|| (aTheta-0.0)<1){
			//if(abs(nTheta-aTheta)<1.0|| (nTheta)<aTheta){
			Q2 = 4.0 * nE0 * nEp * pow(sin(nTheta*3.1415926/180./2.0),2);
			xbj = Q2/2.0/0.938272/(nE0-nEp);
			//	cerr<<Form("=== E0=%f, Ep=%f, Theta=%f",nE0,nEp,nTheta)<<endl;
			N1++;
			vXbj1.push_back(xbj);
			vXS1.push_back(nXS_Born);
			vXS_Err1.push_back(nXS_Born*nFrac_Err);
			vTheta1.push_back(nTheta);
			vP1.push_back(nP0);
		}
		}
		/*}}}*/

		/* Second  Target:{{{*/
		vector<double> vXbj2, vXS2, vXS_Err2,vP2,vTheta2;
		int N2=0;
		while(!(infile2.eof())){
			infile2 >> nA >> nTheta >> nP0 >> nEp >> nXS_Rad >> nXS_Born >> nXS_CC >> nFrac_Err;

			if(abs(nTheta-aTheta)<1.0||(aTheta-0.0)<1){
				//if(abs(nTheta-aTheta)<1.0|| (nTheta)<aTheta){
				Q2 = 4.0 * nE0 * nEp * pow(sin(nTheta*3.1415926/180./2.0),2);
				xbj = Q2/2.0/0.938272/(nE0-nEp);
				//	cerr<<Form("===  E0=%f, Ep=%f, Theta=%f",nE0,nEp,nTheta)<<endl;
				N2++;
				vXbj2.push_back(xbj);
				vXS2.push_back(nXS_Born);
				vXS_Err2.push_back(nXS_Born*nFrac_Err);
				vTheta2.push_back(nTheta);
				vP2.push_back(nP0);
			}
			}
			/*}}}*/

			/*Ratio{{{*/  
			int Count=0;
			Double_t x1,x2,ratio,err;
			vector<Double_t> vXbj, vXbj_Err,vR, vR_Err;

			for(int i=0;i<N1;i++){
				x1 = vXbj1[i]; 
				for(int j=0;j<N2;j++){
					x2 = vXbj2[j];
					if(abs(x1-x2)<0.0001 && abs(vP1[i]-vP2[j])<0.1&& abs(vTheta1[i]-vTheta2[j])<1.0){
						ratio = factor*vXS1[i]/vXS2[j];
						err = ratio * sqrt( pow(vXS_Err2[j]/vXS2[j],2) + pow(vXS_Err1[i]/vXS1[i],2) );
						if(ratio>1e-30 && ratio<100.&&(err/ratio)<0.5){
							vXbj.push_back(x1);
							vXbj_Err.push_back(0.0);
							vR.push_back(ratio);
							vR_Err.push_back(err);
							cerr <<Form("-----> Found one: xbj1=%f, xbj2=%f, XS1=%f, XS2=%f,Ratio=%f ",x1,x2,vXS1[i],vXS2[j],factor*vXS1[i]/vXS2[j])<<endl;
							Count++;
							outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e", x1,ratio, vXS1[i], vXS2[j],err, vXS_Err1[i], vXS_Err2[j] )<<endl;
						}
					}
				}
			}

			//Return the value
			for(int k=0; k<Count; k++){
				aXbj[aN[0]+k] = vXbj[k];
				aR_EX[aN[0]+k] = vR[k];
				aR_EX_Err[aN[0]+k] = vR_Err[k];
			}
			aN[0] += Count;
			cerr<<Form("*****In E02019****** Count = %d, Factor =%f ",Count, factor)<<endl;
			outfile.close();
			/*}}}*/

}
/*}}}*/

/*gGetTargetAZ{{{*/
void gGetTargetAZ(const TString& aTarget, int* aA, int* aZ){
	if(aTarget=="H2"||aTarget=="D2"){
		aA[0] = 2; aZ[0] = 1;
	}
	else if(aTarget=="He3"){
		aA[0] = 3; aZ[0] = 2;
	}
	else if(aTarget=="He4"){
		aA[0] = 4; aZ[0] = 2;
	}
	else if(aTarget=="C12"){
		aA[0] = 12; aZ[0] = 6;
	}
	else if(aTarget=="Ca40"){
		aA[0] = 40; aZ[0] = 20;
	}
	else if(aTarget=="Ca48"){
		aA[0] = 48; aZ[0] = 20;
	}
	else{
		cerr<<" **** I don't know this target:  "<<aTarget.Data()<<endl;
		aA[0]=0; aZ[0]=0;
	} 
}
/*}}}*/

/*E02-019 A/He3{{{*/
void E02019_A_He3(const TString& aTarget, const double aTheta,double* aXbj, double* aR_EX, double* aR_EX_Err_Up,double* aR_EX_Err_Down, int* aN){
	TString aInputFile = aInputFilePath + "Nadia_A_He3.dat";
	ifstream outfile(aInputFile);
	Double_t nTheta,nXbj,nRatio,nErr1,nErr2;
	Double_t aErr_Up,aErr_Down;
	int aA,aZ,nA;
	gGetTargetAZ(aTarget.Data(), &aA,&aZ);

	int aNNN = 0;
	while(!outfile.eof()){
		outfile >> nA >> nTheta >> nXbj >> nRatio >> nErr1 >> nErr2;
		if(abs(nA-aA)<1.0&&(abs(aTheta-nTheta)<1.0 ||(aTheta-0.0)<1.0)&&nRatio>=1e-33){
			aXbj[aNNN] = nXbj;
			aR_EX[aNNN] = nRatio;
			aErr_Up = abs(nErr1 - nRatio);
			aErr_Down = abs(nRatio - nErr2);	
			aR_EX_Err_Up[aNNN] = aErr_Up;
			aR_EX_Err_Down[aNNN] = aErr_Down;
			aNNN++;
		}
	}
	aN[0]=aNNN;
	outfile.close();
}
/*}}}*/

/*E02-019 A/He3{{{*/
void E02019_He4_He3(const TString& aTarget, const double aTheta,double* aXbj, double* aR_EX, double* aR_EX_Err_Up,double* aR_EX_Err_Down, int* aN){
	TString aInputFile = aInputFilePath + "Nadia_A_He3.dat";
	ifstream outfile(aInputFile);
	Double_t nTheta,nXbj,nRatio,nErr,nErr1,nErr2;
	Double_t aErr_Up,aErr_Down;
	int aA,aZ,nA;
	gGetTargetAZ(aTarget.Data(), &aA,&aZ);
	double aXbj_Max = 1.55;
	int aNNN = 0;
	while(!outfile.eof()){
		outfile >> nA >> nTheta >> nXbj >> nRatio >> nErr1 >> nErr2;
		if(abs(nA-aA)<1.0&&(abs(aTheta-nTheta)<1.0 ||(aTheta-0.0)<1.0)&&nRatio>=1e-33&&nXbj<=aXbj_Max){
			aXbj[aNNN] = nXbj;
			aR_EX[aNNN] = nRatio;
			aErr_Up = abs(nErr1 - nRatio);
			aErr_Down = abs(nRatio - nErr2);	
			aR_EX_Err_Up[aNNN] = aErr_Up;
			aR_EX_Err_Down[aNNN] = aErr_Down;
			aNNN++;
		}
	}

	TString aInputFile1 = aInputFilePath + "Nadia_He4_He3.dat";
	ifstream outfile1(aInputFile1);
	while(!outfile1.eof()){
		outfile1 >> nXbj >> nRatio >> nErr;
		aXbj[aNNN] = nXbj;
		aR_EX[aNNN] = 1./nRatio;
		aErr_Up = 1./(nRatio-nErr);
		aErr_Down = 1./(nRatio + nErr);	
		aR_EX_Err_Up[aNNN] = aErr_Up - 1./nRatio;
		aR_EX_Err_Down[aNNN] = 1./nRatio - aErr_Down;
		aNNN++;
	}
	aN[0]=aNNN;
	outfile.close();
	outfile1.close();
}
/*}}}*/

/*E02-019 A/He4{{{*/
void E02019_A_He4(const TString& aTarget, const double aTheta,double* aXbj, double* aR_EX, double* aR_EX_Err, int* aN){
	TString aInputFile = aInputFilePath + "Nadia_A_He4.dat";
	ifstream infile(aInputFile);
	Double_t nTheta,nXbj,nRatio,nErr,dummy;
	int aA,aZ,nA, A_He4;
	gGetTargetAZ(aTarget.Data(), &aA,&aZ);
        TString comment;
        infile>>comment>>comment>>comment>>comment>>comment>>comment>>comment>>comment>>comment>>comment>>comment>>comment;

	int aNNN = 0;
	while(!infile.eof()){
		infile >> A_He4 >> nA >> dummy>> nTheta >> dummy >> nXbj >> nRatio >> nErr >> dummy >> dummy >> dummy >> dummy;
		if(abs(nA-aA)<1.0&&(abs(aTheta-nTheta)<1.0 ||(aTheta-0.0)<1.0)&&nRatio>=1e-33){
			aXbj[aNNN] = nXbj;
			aR_EX[aNNN] = nRatio;
			aR_EX_Err[aNNN] = nErr;
			aNNN++;
		}
	}
	aN[0]=aNNN;
	infile.close();
}
/*}}}*/

/*CLAS_He4_He3{{{*/
void CLAS_He4_He3( double* aXbj_CS, double* aR_EX_CS, double* aR_EX_Err_CS, int *aN_CS){
	TString aInputFile = aInputFilePath + "CLAS_He4_He3.dat";
	ifstream infile(aInputFile);

	double cXbj, cR, cR_Err;
	int aN = 0;

	while(!(infile.eof())){
		infile >> cXbj >> cR >> cR_Err;	
		aXbj_CS[aN] = cXbj;
		aR_EX_CS[aN] = cR/1.15;
		aR_EX_Err_CS[aN] = cR_Err/1.15;
		aN++;	
	}
	aN_CS[0] = aN;
	infile.close();
}
/*}}}*/

//void Merge(const TString& aInputFileName, double* aXbj, double* aR_EX, double* aR_EX_Err, double* aR_MC, int* aN);
//void Merge25(const TString& Target0, const TString& Target, double* aXbj, double* aR_EX, double* aR_EX_Err, double* aR_MC, int* aN);
//void Merge2325(const TString& Target0, const TString& Target, double* aXbj, double* aR_EX, double* aR_EX_Err, double* aR_MC, int* aN);
//void Merge212325(const TString& Target0, const TString& Target, double* aXbj, double* aR_EX, double* aR_EX_Err, double* aR_MC, int* aN);
//void E02019(const TString& aInputFileName, double aTheta, double* aXbj, double* aR_EX, double* aR_EX_Err, int* aN);
//void E02019_A_He3(const TString& aTarget, const double aTheta,double* aXbj, double* aR_EX, double* aR_EX_Err_Up,double* aR_EX_Err_Down, int* aN);
//void E02019_A_He4(const TString& aTarget, const double aTheta,double* aXbj, double* aR_EX, double* aR_EX_Err,int* aN);
//void E02019_He4_He3(const TString& aTarget, const double aTheta,double* aXbj, double* aR_EX, double* aR_EX_Err_Up,double* aR_EX_Err_Down, int* aN);
//void CLAS_He4_He3( double* aXbj_CS, double* aR_EX_CS, double* aR_EX_Err_CS, int *aN_CS);


#include "XGT2_Main.h"
#include "/work/halla/e08014/disk1/yez/Xbj_Cross_Section/SRC/XGT2_XEMC.h"
#include "TLegend.h"
#include "TLine.h"
#include "TGraphAsymmErrors.h"

//const double He4_Norm =1.0/0.864;
const double He4_Norm =1.0;
bool bPrintMore = kTRUE;
ofstream outlog0;

/*List the Statistical Errors{{{*/
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
/*}}}*/

/*inline double gGet_Total_SystErr(const TString& aTarget_Name, const TString& aArm, const double aTheta){{{*/
inline double gGet_Total_SystErr(const TString& aTarget_Name, const TString& aArm, const double aTheta){
	double total_err = 0.0;

	total_err += pow(SystErr_HRS_Angle/(aTheta*3.1415926/180.0),2.); 
	total_err += pow(SystErr_HRS_Mom,2.); 
	total_err += pow(SystErr_Beam_Energy,2.); 

	if(aTarget_Name=="H2"||aTarget_Name=="He3"||aTarget_Name=="He4")
		total_err += pow( SystErr_Nmc_Cryo,2.); 
	else
		total_err += pow( SystErr_Nmc_Foil,2.); 

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
	h2_err += pow( SystErr_Nmc_Cryo,2.); 
	h2_err += pow( SystErr_Trig_Eff_H2,2.); 
	h2_err += pow( SystErr_Rho_H2,2.); 
	h2_err += pow( SystErr_Boil_H2,2.); 
	h2_err += pow( SystErr_Dummy_H2,2.); 
	h2_err += pow( SystErr_RadC_H2,2.); 
	h2_err += pow( SystErr_CouC_H2,2.); 
	h2_err += pow( SystErr_AccC_H2,2.); 
	double he3_err = 0;
	he3_err += pow( SystErr_Nmc_Cryo,2.); 
	he3_err += pow( SystErr_Trig_Eff_He3,2.); 
	he3_err += pow( SystErr_Rho_He3,2.); 
	he3_err += pow( SystErr_Boil_He3,2.); 
	he3_err += pow( SystErr_Dummy_He3,2.); 
	he3_err += pow( SystErr_RadC_He3,2.); 
	he3_err += pow( SystErr_CouC_He3,2.); 
	he3_err += pow( SystErr_AccC_He3,2.); 
	double he4_err = 0;
	he4_err += pow( SystErr_Nmc_Cryo,2.); 
	he4_err += pow( SystErr_Trig_Eff_He4,2.); 
	he4_err += pow( SystErr_Rho_He4,2.); 
	he4_err += pow( SystErr_Boil_He4,2.); 
	he4_err += pow( SystErr_Dummy_He4,2.); 
	he4_err += pow( SystErr_RadC_He4,2.); 
	he4_err += pow( SystErr_CouC_He4,2.); 
	he4_err += pow( SystErr_AccC_He4,2.); 
	double c12_err = 0;
	c12_err += pow( SystErr_Nmc_Foil,2.); 
	c12_err += pow( SystErr_Trig_Eff_C12,2.); 
	c12_err += pow( SystErr_Rho_C12,2.); 
	c12_err += pow( SystErr_RadC_C12,2.); 
	c12_err += pow( SystErr_CouC_C12,2.); 
	c12_err += pow( SystErr_AccC_C12,2.); 
	double ca40_err = 0;
	ca40_err += pow( SystErr_Nmc_Foil,2.); 
	ca40_err += pow( SystErr_Trig_Eff_Ca40,2.); 
	ca40_err += pow( SystErr_Rho_Ca40,2.); 
	ca40_err += pow( SystErr_RadC_Ca40,2.); 
	ca40_err += pow( SystErr_CouC_Ca40,2.); 
	ca40_err += pow( SystErr_AccC_Ca40,2.); 
	double ca48_err = 0;
	ca48_err += pow( SystErr_Nmc_Foil,2.); 
	ca48_err += pow( SystErr_Trig_Eff_Ca48,2.); 
	ca48_err += pow( SystErr_Rho_Ca48,2.); 
	ca48_err += pow( SystErr_RadC_Ca48,2.); 
	ca48_err += pow( SystErr_CouC_Ca48,2.); 
	ca48_err += pow( SystErr_AccC_Ca48,2.); 

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
		outlog0<<"*** I don't know the target name!!!"<<endl;
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
		outlog0<<"*** I don't know the kinematics name!!!"<<endl;
	return aKin_Name;
}
/*}}}*/

/*Cuts on the edge of Xbj{{{*/
// Cut_L_Min Cut_L_Max Cut_R_Min Cut_R_Max
const double E0 = 3.356;
const double Xbj_Cut_21_1[4] = {1.25, 2.15,1.25,2.15}; 
const double Xbj_Cut_21_2[4] = {1.65, 3.00,1.65,3.00}; 
const double Xbj_Cut_23_1[4] = {1.30, 2.15,1.30,2.15}; 
const double Xbj_Cut_23_2[4] = {1.85, 3.00,1.85,3.00};
const double Xbj_Cut_QE_1[4] = {0.85, 1.20,0.85,1.20}; 
const double Xbj_Cut_QE_2[4] = {1.05, 1.55,1.05,1.55}; 
const double Xbj_Cut_25_1[4] = {1.35, 2.10,1.35,2.10};
const double Xbj_Cut_25_2[4] = {2.00, 3.00,2.00,3.00}; 
const double Xbj_Cut_28_1[4] = {1.80, 3.00,1.80,3.00}; 
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

inline void gGet_Ep_Edge(){
	double Theta = 0.0, SinSQ = 0.0;
	for(int i=0;i<4;i++){
		Theta = 21.00;
		SinSQ = pow(sin(Theta*TMath::DegToRad()/2.0),2.); //Define Sin(Theta/2.)^2
		Ep_Cut_21_1[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*PROTON_MASS*Xbj_Cut_21_1[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Ep_Cut_21_2[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*PROTON_MASS*Xbj_Cut_21_2[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Theta = 23.00;
		SinSQ = pow(sin(Theta*TMath::DegToRad()/2.0),2.); //Define Sin(Theta/2.)^2
		Ep_Cut_23_1[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*PROTON_MASS*Xbj_Cut_23_1[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Ep_Cut_23_2[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*PROTON_MASS*Xbj_Cut_23_2[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Theta = 25.00;
		SinSQ = pow(sin(Theta*TMath::DegToRad()/2.0),2.); //Define Sin(Theta/2.)^2
		Ep_Cut_QE_1[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*PROTON_MASS*Xbj_Cut_QE_1[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Ep_Cut_QE_2[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*PROTON_MASS*Xbj_Cut_QE_2[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Ep_Cut_25_1[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*PROTON_MASS*Xbj_Cut_25_1[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Ep_Cut_25_2[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*PROTON_MASS*Xbj_Cut_25_2[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
		Theta = 28.00;
		SinSQ = pow(sin(Theta*TMath::DegToRad()/2.0),2.); //Define Sin(Theta/2.)^2
		Ep_Cut_28_1[i]=E0/(1.0+4.0*E0*SinSQ/(2.0*PROTON_MASS*Xbj_Cut_28_1[i])); //use xbj = Q2/2Mp/(Ei-Ep),Q2 = 4Ei*Ep*Sin_SQ 
	}
}
/*}}}*/

/*Get He3 RadCorr{{{*/
inline double gGet_RadCorr_He3(const double aXbj){
	double aRadCor = 1-0.1*(aXbj-2.45)+0.025*pow((aXbj-2.45),2.)-0.72*pow((aXbj-2.45),3);
	//return 1.0/aRadCor;
	return 1.0;
}
/*}}}*/

void Merge(const TString& aInputFileName,
		 double* aXbj_L1, double* aR_EX_L1, double* aR_EX_Err_L1, double* aR_MC_L1, int* aN_L1,
		 double* aXbj_L2, double* aR_EX_L2, double* aR_EX_Err_L2, double* aR_MC_L2, int* aN_L2,
		 double* aXbj_R1, double* aR_EX_R1, double* aR_EX_Err_R1, double* aR_MC_R1, int* aN_R1,
		 double* aXbj_R2, double* aR_EX_R2, double* aR_EX_Err_R2, double* aR_MC_R2, int* aN_R2
		);
TString Target0,Target,Com0,Com;
/*Comment{{{*/
/*Format in aFileName:
  Target 1:
  line#1 --> The first  setting of each angle on  L-HRS, like L_Kin3.1 ...
  line#2 --> The second setting of each angle on  L-HRS, like L_Kin3.2 ...
  line#3 --> The first  setting of each angle on  R-HRS, like R_Kin3.1 ...
  line#4 --> The second setting of each angle on  R-HRS, like R_Kin3.2 ...
  Target 2:  
  line#5 --> The first  setting of each angle on  L-HRS, like L_Kin3.1 ...
  line#6 --> The second setting of each angle on  L-HRS, like L_Kin3.2 ...

  line#7 --> The first  setting of each angle on  R-HRS, like R_Kin3.1 ...
  line#8 --> The second setting of each angle on  R-HRS, like R_Kin3.2 ...
  */
/*}}}*/

/*main{{{*/
int main()
{
	/*ROOT Define{{{*/
	// Fill color
	gStyle->SetStatColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetPadColor(0);
	gStyle->SetFrameFillColor(0);

	// Border mode
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPalette(1,0);

	// Font
	gStyle->SetTextFont(32);
	gStyle->SetLabelFont(32, "xyz");
	gStyle->SetTitleFont(22, "xyz");
	gStyle->SetStatFont(32);
	gStyle->SetTitleFillColor(0);

	// Opt
	//    gStyle->SetOptDate(0);
	//    gStyle->SetOptTitle(1);
	//    gStyle->SetOptStat(1);
	gStyle->SetOptFit(1);
	//    // Margin
	// //    gStyle->SetPadLeftMargin(0.1);
	// //    gStyle->SetPadRightMargin(0.1);
	// //    gStyle->SetPadTopMargin(0.1);
	// //    gStyle->SetPadBottomMargin(0.1);


	//void HallA_style() {
	gROOT->SetStyle("Plain");
	gStyle->SetPaperSize(TStyle::kUSLetter);
	gStyle->SetPaperSize(18,22);
	gStyle->SetOptFit(1111);
	gStyle->SetPalette(1);
	gStyle->SetNdivisions(505);

	gStyle->SetCanvasColor(0);
	gStyle->SetPadTopMargin(.05);
	gStyle->SetPadLeftMargin(.15);
	gStyle->SetPadRightMargin(.1);
	gStyle->SetPadBottomMargin(.15);
	gStyle->SetTitleYOffset(1.3);
	gStyle->SetLabelFont(32,"X");
	gStyle->SetLabelFont(32,"Y");

	// prepare gStyle to be useful
	//   1 = solid
	//   2 = long dash (30 10)
	gStyle->SetTitleFillColor(-1); 
	//   3 = dotted (4 8)
	//   4 = dash-dot (15 12 4 12)
	//   5 = short dash ( 15 15 )
	//   6 = dash-dot-dot 
	gStyle->SetLineStyleString(1,"[]");
	gStyle->SetLineStyleString(2,"[30 10]");
	gStyle->SetLineStyleString(3,"[4 8]");
	gStyle->SetLineStyleString(4,"[15 12 4 12]");
	gStyle->SetLineStyleString(5,"[15 15]");
	gStyle->SetLineStyleString(6,"[15 12 4 12 4 12]");
	gStyle->SetLabelSize(0.05,"X");
	gStyle->SetLabelSize(0.05,"Y");
	gStyle->SetNdivisions(505,"Y");
	gStyle->SetOptDate(0);
	gStyle->SetDateY(.98);
	gStyle->SetStripDecimals(kFALSE);

	gStyle->SetHistFillColor(0); 
	gStyle->SetFillColor(0); 
	gStyle->SetFillStyle(4000); 
	gStyle->SetStatStyle(0); 
	gStyle->SetTitleStyle(0); 
	gStyle->SetCanvasBorderSize(0); 
	gStyle->SetFrameBorderSize(0); 
	gStyle->SetLegendBorderSize(0); 
	gStyle->SetStatBorderSize(0); 
	gStyle->SetTitleBorderSize(0); 

	/*}}}*/

	cerr<<" 1 vs 2 (He3 or He4 or C12) for 1 = "; cin >> Target0;
	cerr<<" 1 vs 2 (H2  or He3 or He4) for 2 = "; cin >> Target;
	cerr<<" Com for 1 = "; cin >> Com0;
	cerr<<" Com for 2 = "; cin >> Com;

    outlog0.open(Form("log_%s_%s_%s_%s.txt", Target0.Data(), Target.Data(), Com0.Data(),Com.Data()));

	gGet_Ep_Edge();//Get Ep Range from Xbj edge
	int A1 = 0, A2 = 0, Z1 = 0, Z2=0;
	/*Get Target Info 1{{{*/
	if(Target0 == "H2"||Target == "D2"){
		A1 = 2; Z1 = 1;  
	}
	else if(Target0 == "He3"){
		A1 = 3; Z1 = 2;  
	}
	else if(Target0 == "He4"){
		A1 = 4; Z1 = 2; 
	}
	else if(Target0 == "Be"){
		A1 = 9; Z1 = 4; 
	}
	else if(Target0 == "C12"){
		A1 = 12; Z1 = 6; 
	}
	else if(Target0 == "Al"){
		A1 = 27; Z1 = 13; 
	}
	else if(Target0 == "Ca40"){
		A1 = 40; Z1 = 20;
	}
	else if(Target0 == "Ca48"){
		A1 = 48; Z1 = 20; 
	}
	else
		outlog0<<" **** ERROR, I don't know the target!!!"<<endl;
	/*}}}*/
	/*Get Target Info 2{{{*/
	if(Target == "H2"||Target == "D2"){
		A2 = 2; Z2 = 1;  
	}
	else if(Target == "He3"){
		A2 = 3; Z2 = 2;  
	}
	else if(Target == "He4"){
		A2 = 4; Z2 = 2; 
	}
	else if(Target == "Be"){
		A2 = 9; Z2 = 4; 
	}
	else if(Target == "C12"){
		A2 = 12; Z2 = 6; 
	}
	else if(Target == "Al"){
		A2 = 27; Z2 = 13; 
	}
	else if(Target == "Ca40"){
		A2 = 40; Z2 = 20;
	}
	else if(Target == "Ca48"){
		A2 = 48; Z2 = 20; 
	}
	else
		outlog0<<" **** ERROR, I don't know the target!!!"<<endl;
	/*}}}*/

	/*Get Ratio{{{*/
	int Theta =21;
	double Zero[100] = {100*0.0};

	double xbj_21_L1[100], R_EX_21_L1[100], R_EX_Err_21_L1[100], R_MC_21_L1[100];
	double xbj_21_L2[100], R_EX_21_L2[100], R_EX_Err_21_L2[100], R_MC_21_L2[100];
	double xbj_21_R1[100], R_EX_21_R1[100], R_EX_Err_21_R1[100], R_MC_21_R1[100];
	double xbj_21_R2[100], R_EX_21_R2[100], R_EX_Err_21_R2[100], R_MC_21_R2[100];
	int N_21_L1 = 0, N_21_L2 = 0, N_21_R1 = 0, N_21_R2 = 0;
	Merge(Form("./input_kin/R21_%s_%s.rt",Target0.Data(),Target.Data()), 
			xbj_21_L1, R_EX_21_L1, R_EX_Err_21_L1, R_MC_21_L1, &N_21_L1,
			xbj_21_L2, R_EX_21_L2, R_EX_Err_21_L2, R_MC_21_L2, &N_21_L2,
			xbj_21_R1, R_EX_21_R1, R_EX_Err_21_R1, R_MC_21_R1, &N_21_R1,
			xbj_21_R2, R_EX_21_R2, R_EX_Err_21_R2, R_MC_21_R2, &N_21_R2
			);
	outlog0<<Form("@@@@@@@@@@ Theta=21:  N_1 = %d, N_2 = %d, N_3 = %d, N_4 = %d", N_21_L1, N_21_L2, N_21_R1, N_21_R2)<<endl;

	double xbj_23_L1[100], R_EX_23_L1[100], R_EX_Err_23_L1[100], R_MC_23_L1[100];
	double xbj_23_L2[100], R_EX_23_L2[100], R_EX_Err_23_L2[100], R_MC_23_L2[100];
	double xbj_23_R1[100], R_EX_23_R1[100], R_EX_Err_23_R1[100], R_MC_23_R1[100];
	double xbj_23_R2[100], R_EX_23_R2[100], R_EX_Err_23_R2[100], R_MC_23_R2[100];
	int N_23_L1 = 0, N_23_L2 = 0, N_23_R1 = 0, N_23_R2 = 0;
	if(!(Target=="H2"))
		Merge(Form("./input_kin/R23_%s_%s.rt",Target0.Data(),Target.Data()), 
				xbj_23_L1, R_EX_23_L1, R_EX_Err_23_L1, R_MC_23_L1, &N_23_L1,
				xbj_23_L2, R_EX_23_L2, R_EX_Err_23_L2, R_MC_23_L2, &N_23_L2,
				xbj_23_R1, R_EX_23_R1, R_EX_Err_23_R1, R_MC_23_R1, &N_23_R1,
				xbj_23_R2, R_EX_23_R2, R_EX_Err_23_R2, R_MC_23_R2, &N_23_R2
				);
	outlog0<<Form("@@@@@@@@@@ Theta=23:  N_1 = %d, N_2 = %d, N_3 = %d, N_4 = %d", N_23_L1, N_23_L2, N_23_R1, N_23_R2)<<endl;

	double xbj_QE_L1[100], R_EX_QE_L1[100], R_EX_Err_QE_L1[100], R_MC_QE_L1[100];
	double xbj_QE_L2[100], R_EX_QE_L2[100], R_EX_Err_QE_L2[100], R_MC_QE_L2[100];
	double xbj_QE_R1[100], R_EX_QE_R1[100], R_EX_Err_QE_R1[100], R_MC_QE_R1[100];
	double xbj_QE_R2[100], R_EX_QE_R2[100], R_EX_Err_QE_R2[100], R_MC_QE_R2[100];
	int N_QE_L1 = 0, N_QE_L2 = 0, N_QE_R1 = 0, N_QE_R2 = 0;
	if(!(Target=="H2"))
		Merge(Form("./input_kin/RQE_%s_%s.rt",Target0.Data(),Target.Data()), 
				xbj_QE_L1, R_EX_QE_L1, R_EX_Err_QE_L1, R_MC_QE_L1, &N_QE_L1,
				xbj_QE_L2, R_EX_QE_L2, R_EX_Err_QE_L2, R_MC_QE_L2, &N_QE_L2,
				xbj_QE_R1, R_EX_QE_R1, R_EX_Err_QE_R1, R_MC_QE_R1, &N_QE_R1,
				xbj_QE_R2, R_EX_QE_R2, R_EX_Err_QE_R2, R_MC_QE_R2, &N_QE_L2
				);
	outlog0<<Form("@@@@@@@@@@ Theta=QE:  N_1 = %d, N_2 = %d, N_3 = %d, N_4 = %d", N_QE_L1, N_QE_L2, N_QE_R1, N_QE_R2)<<endl;

	double xbj_25_L1[100], R_EX_25_L1[100], R_EX_Err_25_L1[100], R_MC_25_L1[100];
	double xbj_25_L2[100], R_EX_25_L2[100], R_EX_Err_25_L2[100], R_MC_25_L2[100];
	double xbj_25_R1[100], R_EX_25_R1[100], R_EX_Err_25_R1[100], R_MC_25_R1[100];
	double xbj_25_R2[102], R_EX_25_R2[100], R_EX_Err_25_R2[100], R_MC_25_R2[100];
	int N_25_L1 = 0, N_25_L2 = 0, N_25_R1 = 0, N_25_R2 = 0;
	Merge(Form("./input_kin/R25_%s_%s.rt",Target0.Data(),Target.Data()),
		   	xbj_25_L1, R_EX_25_L1, R_EX_Err_25_L1, R_MC_25_L1, &N_25_L1,
		   	xbj_25_L2, R_EX_25_L2, R_EX_Err_25_L2, R_MC_25_L2, &N_25_L2,
		   	xbj_25_R1, R_EX_25_R1, R_EX_Err_25_R1, R_MC_25_R1, &N_25_R1,
		   	xbj_25_R2, R_EX_25_R2, R_EX_Err_25_R2, R_MC_25_R2, &N_25_R2
			);

	double xbj_28_L1[100], R_EX_28_L1[100], R_EX_Err_28_L1[100], R_MC_28_L1[100];
	double xbj_28_L2[100], R_EX_28_L2[100], R_EX_Err_28_L2[100], R_MC_28_L2[100];
	double xbj_28_R1[100], R_EX_28_R1[100], R_EX_Err_28_R1[100], R_MC_28_R1[100];
	double xbj_28_R2[100], R_EX_28_R2[100], R_EX_Err_28_R2[100], R_MC_28_R2[100];
	int N_28_L1 = 0, N_28_L2 = 0, N_28_R1 = 0, N_28_R2 = 0;
	if((Target0=="C12" && Target=="He3")||(Target=="C12" && Target0=="He3")){
		Merge(Form("./input_kin/R28_%s_%s.rt",Target0.Data(),Target.Data()), 
				xbj_28_L1, R_EX_28_L1, R_EX_Err_28_L1, R_MC_28_L1, &N_28_L1,
				xbj_28_L2, R_EX_28_L2, R_EX_Err_28_L2, R_MC_28_L2, &N_28_L2,
				xbj_28_R1, R_EX_28_R1, R_EX_Err_28_R1, R_MC_28_R1, &N_28_R1,
				xbj_28_R2, R_EX_28_R2, R_EX_Err_28_R2, R_MC_28_R2, &N_28_R2
				);
	}
	outlog0<<Form("@@@@@@@@@@ Theta=28:  N_1 = %d, N_2 = %d, N_3 = %d, N_4 = %d", N_28_L1, N_28_L2, N_28_R1, N_28_R2)<<endl;
	/*}}}*/

	/*Plot{{{*/
	outlog0<<endl<<"@@@@@@@@ Now starting to make some plots ..."<<endl;

	gStyle->SetOptStat(0);
    /*Ranges{{{*/
	double RMAX = 10.0,RMIN=0.4;	double XMax = 3.2;
	if(Target=="He4")
		XMax=3.2;
	if(Target=="He3")
		XMax=3.2;
	if(Target=="H2")
		XMax=2.2;

	if(Target=="He3" &&Target0=="C12")
		RMAX = 20.0;
	if(Target=="He3" &&Target0=="He4")
		RMAX = 8.0;
	if(Target=="He4" &&Target0=="C12"){
		RMIN = 0.8; RMAX = 6.0;
	}
	if(Target=="Ca40" &&Target0=="Ca48"){
		RMAX = 1.5; RMIN=0.5;
	}
	if(Target=="Ca48" &&Target0=="Ca40"){
		RMAX = 1.5; RMIN=0.5;
	}
	if(Target=="C12" &&Target0=="Ca40")
		RMAX = 1.5;
	if(Target=="C12" &&Target0=="Ca48")
		RMAX = 1.5;
	if(Target=="H2" &&Target0=="He3")
		RMAX = 3.0;
	if(Target=="H2" &&Target0=="He4")
		RMAX = 5.1;
	if(Target=="H2" &&Target0=="C12"){
		RMIN=0.1; RMAX = 7.5;
	}
	if(Target=="H2" &&Target0=="Ca40"){
		RMIN=0.1; RMAX = 9.5;
	}
	if(Target=="H2" &&Target0=="Ca48"){
		RMIN=0.1; RMAX = 9.5;
	}
	if(Target=="He4" &&Target0=="He3"){
		RMIN=0.0; RMAX = 1.0;
	}
	if(Target=="C12" &&Target0=="C12"){
		RMIN=0.7; RMAX = 1.3;
	}
	if(Target=="C12" &&Target0=="He3"){
		RMIN=0.0; RMAX = 1.0;
	}
	if(Target=="C12" &&Target0=="He4"){
		RMIN=0.0; RMAX = 1.0;
	}
	/*}}}*/

	/*histo{{{*/
	TCanvas *c3 = new TCanvas("c3","c3",1200,700);
	c3->cd();
	TH2F *h3 = new TH2F("h3","",300,0.7,XMax,300,RMIN,RMAX);
	h3->SetStats(kFALSE);
	h3->SetXTitle("x");
	h3->GetXaxis()->CenterTitle(1);
	h3->GetXaxis()->SetTitleFont(22);
	h3->GetXaxis()->SetTitleSize(0.08);
	h3->GetXaxis()->SetTitleOffset(0.7);
	h3->GetYaxis()->SetTitle(Form("#frac{#sigma_{%s}}{#sigma_{%s}} #times #frac{%d}{%d}",Target0.Data(),Target.Data(),A2,A1));
	h3->GetYaxis()->CenterTitle(1);
	h3->GetYaxis()->SetTitleFont(22);
	h3->GetYaxis()->SetTitleSize(0.07);
	h3->GetYaxis()->SetTitleOffset(0.8);
	h3->GetYaxis()->CenterTitle();
	gPad->SetLogy(0);
	h3->Draw();

	TH2F *h4 = new TH2F("h4","",300,0.7,1.4,300,0.5,1.5);
	//TH2F *h4 = new TH2F("h4","",300,0.7,1.4,300,RMIN,2.);
	h4->SetStats(kFALSE);
	h4->SetXTitle("x");
	h4->GetXaxis()->CenterTitle(1);
	h4->GetXaxis()->SetTitleFont(22);
	h4->GetXaxis()->SetTitleSize(0.08);
	h4->GetXaxis()->SetTitleOffset(0.7);
	h4->GetYaxis()->SetTitle(Form("#frac{#sigma_{%s}}{#sigma_{%s}} #times #frac{%d}{%d}",Target0.Data(),Target.Data(),A2,A1));
	h4->GetYaxis()->CenterTitle(1);
	h4->GetYaxis()->SetTitleFont(22);
	h4->GetYaxis()->SetTitleSize(0.07);
	h4->GetYaxis()->SetTitleOffset(0.8);
	h4->GetYaxis()->CenterTitle();
	gPad->SetLogy(0);
	h4->Draw();


	if(Target=="He3" &&Target0=="C12")
		//RMAX = 10.0;
		RMAX = 5.0;
	if(Target=="He3" &&Target0=="He4")
		RMAX = 8.0;
	if(Target=="He4" &&Target0=="C12")
		RMAX = 5.5;
	if(Target=="Ca40" &&Target0=="Ca48"){
		RMIN = 0.8;		RMAX = 1.25;
	}
	if(Target=="C12" &&Target0=="Ca40"){
		RMAX = 1.5; RMIN=0.7;
	}
	if(Target=="C12" &&Target0=="Ca48"){
		RMAX = 1.5; RMIN=0.7;
	}
	if(Target=="H2" &&Target0=="C12"){
		RMIN=0.1;
	}
	/*}}}*/

	double lx_min = 0.17, lx_max=0.50;
	if((Target=="He4" &&Target0=="He3")||(Target=="C12" &&Target0=="He3")||(Target=="C12" &&Target0=="He4")){
		lx_min+=0.3; lx_max+=0.3;
	}

	/* Degree 21{{{*/
	TLegend *l1 = new TLegend(lx_min,0.60,lx_max, 0.94,Form("#sigma_{%s} / #sigma_{%s} Ratio: ",Target0.Data(),Target.Data()));
	l1->SetTextSize(0.043);
	l1->SetTextFont(32);

	c3->cd(); c3->Clear(); h3->Draw();	Theta = 21;
	if(N_21_L1>1){
		TGraphErrors *ex21_L1 = new TGraphErrors(N_21_L1,xbj_21_L1, R_EX_21_L1, Zero,R_EX_Err_21_L1);
		ex21_L1->SetMarkerStyle(20);
		ex21_L1->SetMarkerSize(1.5);
		ex21_L1->SetMarkerColor(1);
		ex21_L1->SetLineColor(1);
		ex21_L1->Draw("P");
		l1->AddEntry(ex21_L1, Form("Kin3.1 on HRS-L"),"p");
	}
	if(N_21_L2>1){
		TGraphErrors *ex21_L2 = new TGraphErrors(N_21_L2,xbj_21_L2, R_EX_21_L2, Zero,R_EX_Err_21_L2);
		ex21_L2->SetMarkerStyle(21);
		ex21_L2->SetMarkerSize(1.5);
		ex21_L2->SetMarkerColor(2);
		ex21_L2->SetLineColor(2);
		ex21_L2->Draw("P");
		l1->AddEntry(ex21_L2, Form("Kin3.2 on HRS-L"),"p");
	}
	if(N_21_R1>1){
		TGraphErrors *ex21_R1 = new TGraphErrors(N_21_R1,xbj_21_R1, R_EX_21_R1, Zero,R_EX_Err_21_R1);
		ex21_R1->SetMarkerStyle(22);
		ex21_R1->SetMarkerSize(1.5);
		ex21_R1->SetMarkerColor(4);
		ex21_R1->SetLineColor(4);
		ex21_R1->Draw("P");
		l1->AddEntry(ex21_R1, Form("Kin3.1 on HRS-R"),"p");
	}
	if(N_21_R2>1){
		TGraphErrors *ex21_R2 = new TGraphErrors(N_21_R2,xbj_21_R2, R_EX_21_R2, Zero,R_EX_Err_21_R2);
		ex21_R2->SetMarkerStyle(23);
		ex21_R2->SetMarkerSize(1.5);
		ex21_R2->SetMarkerColor(6);
		ex21_R2->SetLineColor(26);
		ex21_R2->Draw("P");
		l1->AddEntry(ex21_R2, Form("Kin3.2 on HRS-R"),"p");
	}
	l1->Draw();
	c3->Print(Form("./kin/A%d_%s_%s_Ratio_%s_%s.png",Theta,Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	c3->Print(Form("./kin/A%d_%s_%s_Ratio_%s_%s.pdf",Theta,Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	/*}}}*/

	/*Degree 23{{{*/
	TLegend *l2 = new TLegend(lx_min,0.60,lx_max, 0.94,Form("#sigma_{%s} / #sigma_{%s} Ratio: ",Target0.Data(),Target.Data()));
	l2->SetTextSize(0.043);
	l2->SetTextFont(32);

	c3->cd(); c3->Clear(); h3->Draw(); Theta = 23;
	if(N_23_L1>1){
		TGraphErrors *ex23_L1 = new TGraphErrors(N_23_L1,xbj_23_L1, R_EX_23_L1, Zero,R_EX_Err_23_L1);
		ex23_L1->SetMarkerStyle(20);
		ex23_L1->SetMarkerSize(1.5);
		ex23_L1->SetMarkerColor(1);
		ex23_L1->SetLineColor(1);
		if(!(Target=="H2")){
			ex23_L1->Draw("P");
			if((Target0=="C12" && Target=="He4")||(Target0=="He4" && Target=="He3"))
				l2->AddEntry(ex23_L1, Form("Kin4.2 on HRS-L"),"p");
			else	
				l2->AddEntry(ex23_L1, Form("Kin4.1 on HRS-L"),"p");
		}
	}
	if(N_23_L2>1){
		TGraphErrors *ex23_L2 = new TGraphErrors(N_23_L2,xbj_23_L2, R_EX_23_L2, Zero,R_EX_Err_23_L2);
		ex23_L2->SetMarkerStyle(21);
		ex23_L2->SetMarkerSize(1.5);
		ex23_L2->SetMarkerColor(2);
		ex23_L2->SetLineColor(2);
		if(!(Target=="H2")){
			ex23_L2->Draw("P");
			if((Target0=="C12" && Target=="He4")||(Target0=="He4" && Target=="He3"))
				l2->AddEntry(ex23_L2, Form("Kin4.2 on HRS-R"),"p");
			else
				l2->AddEntry(ex23_L2, Form("Kin4.2 on HRS-L"),"p");
		}
	}
	if(N_23_R1>1){
		TGraphErrors *ex23_R1 = new TGraphErrors(N_23_R1,xbj_23_R1, R_EX_23_R1, Zero,R_EX_Err_23_R1);
		ex23_R1->SetMarkerStyle(22);
		ex23_R1->SetMarkerSize(1.5);
		ex23_R1->SetMarkerColor(4);
		ex23_R1->SetLineColor(4);
		if(!(Target=="H2")){
			ex23_R1->Draw("P");
				l2->AddEntry(ex23_R1, Form("Kin4.1 on HRS-R"),"p");
		}
	}
	if(N_23_R2>1){
		TGraphErrors *ex23_R2 = new TGraphErrors(N_23_R2,xbj_23_R2, R_EX_23_R2, Zero,R_EX_Err_23_R2);
		ex23_R2->SetMarkerStyle(23);
		ex23_R2->SetMarkerSize(1.5);
		ex23_R2->SetMarkerColor(6);
		ex23_R2->SetLineColor(6);
		if(!(Target=="H2")){
			ex23_R2->Draw("P");
			l2->AddEntry(ex23_R2, Form("Kin4.2 on HRS-R"),"p");
		}
	}
	l2->Draw();
	c3->Print(Form("./kin/A%d_%s_%s_Ratio_%s_%s.png",Theta,Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	c3->Print(Form("./kin/A%d_%s_%s_Ratio_%s_%s.pdf",Theta,Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
		/*}}}*/

	/* QE Degree{{{*/
/*	TLegend *l3 = new TLegend(lx_min,0.60,lx_max, 0.94,Form("#sigma_{%s} / #sigma_{%s} Ratio: ",Target0.Data(),Target.Data()));
	l3->SetTextSize(0.043);
	l3->SetTextFont(32);

	c3->cd(); c3->Clear(); h4->Draw(); Theta = 25;
	if(N_QE_L1>1){
		TGraphErrors *exQE_L1 = new TGraphErrors(N_QE_L1,xbj_QE_L1, R_EX_QE_L1, Zero,R_EX_Err_QE_L1);
		exQE_L1->SetMarkerStyle(20);
		exQE_L1->SetMarkerSize(1.5);
		exQE_L1->SetMarkerColor(1);
		exQE_L1->SetLineColor(1);
		if(!(Target=="H2")){
			exQE_L1->Draw("P");
			l3->AddEntry(exQE_L1, Form("Kin5.0 HRS-L"),"p");
		}
	}
	if(N_QE_L2>1){
		TGraphErrors *exQE_L2 = new TGraphErrors(N_QE_L2,xbj_QE_L2, R_EX_QE_L2, Zero,R_EX_Err_QE_L2);
		exQE_L2->SetMarkerStyle(21);
		exQE_L2->SetMarkerSize(1.5);
		exQE_L2->SetMarkerColor(2);
		exQE_L2->SetLineColor(2);
		if(!(Target=="H2")){
			exQE_L2->Draw("P");
			l3->AddEntry(exQE_L2, Form("Kin5.05 HRS-L"),"p");
		}
	}
	if(N_QE_R1>1){
		TGraphErrors *exQE_R1 = new TGraphErrors(N_QE_R1,xbj_QE_R1, R_EX_QE_R1, Zero,R_EX_Err_QE_R1);
		exQE_R1->SetMarkerStyle(22);
		exQE_R1->SetMarkerSize(1.5);
		exQE_R1->SetMarkerColor(4);
		exQE_R1->SetLineColor(4);
		if(!(Target=="H2")){
			exQE_R1->Draw("P");
			l3->AddEntry(exQE_R1, Form("Kin5.0 HRS-R"),"p");
		}
	}
	if(N_QE_R2>1){
		TGraphErrors *exQE_R2 = new TGraphErrors(N_QE_R2,xbj_QE_R2, R_EX_QE_R2, Zero,R_EX_Err_QE_R2);
		exQE_R2->SetMarkerStyle(23);
		exQE_R2->SetMarkerSize(1.5);
		exQE_R2->SetMarkerColor(6);
		exQE_R2->SetLineColor(6);
		if(!(Target=="H2")){
			exQE_R2->Draw("P");
			l3->AddEntry(exQE_R2, Form("Kin5.05 HRS-R"),"p");
		}
	}
	l3->Draw();
	c3->Print(Form("./kin/AQE_%s_%s_Ratio_%s_%s.png",Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	c3->Print(Form("./kin/AQE_%s_%s_Ratio_%s_%s.pdf",Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
*/	
	/*}}}*/

	/*Degree 25 {{{*/
	TLegend *l4 = new TLegend(lx_min,0.60,lx_max, 0.94,Form("#sigma_{%s} / #sigma_{%s} Ratio: ",Target0.Data(),Target.Data()));
	l4->SetTextSize(0.043);
	l4->SetTextFont(32);

	c3->cd(); c3->Clear(); h3->Draw(); Theta = 25;
	if(N_QE_L1>1){
		TGraphErrors *exQE_L1 = new TGraphErrors(N_QE_L1,xbj_QE_L1, R_EX_QE_L1, Zero,R_EX_Err_QE_L1);
		exQE_L1->SetMarkerStyle(24);
		exQE_L1->SetMarkerSize(1.5);
		exQE_L1->SetMarkerColor(1);
		exQE_L1->SetLineColor(1);
		if(!(Target=="H2")){
			exQE_L1->Draw("P");
			l4->AddEntry(exQE_L1, Form("Kin5.0 HRS-L"),"p");
		}
	}
	if(N_QE_L2>1){
		TGraphErrors *exQE_L2 = new TGraphErrors(N_QE_L2,xbj_QE_L2, R_EX_QE_L2, Zero,R_EX_Err_QE_L2);
		exQE_L2->SetMarkerStyle(25);
		exQE_L2->SetMarkerSize(1.5);
		exQE_L2->SetMarkerColor(2);
		exQE_L2->SetLineColor(2);
		if(!(Target=="H2")){
			exQE_L2->Draw("P");
			l4->AddEntry(exQE_L2, Form("Kin5.05 HRS-L"),"p");
		}
	}
	if(N_QE_R1>1){
		TGraphErrors *exQE_R1 = new TGraphErrors(N_QE_R1,xbj_QE_R1, R_EX_QE_R1, Zero,R_EX_Err_QE_R1);
		exQE_R1->SetMarkerStyle(26);
		exQE_R1->SetMarkerSize(1.5);
		exQE_R1->SetMarkerColor(4);
		exQE_R1->SetLineColor(4);
		if(!(Target=="H2")){
			exQE_R1->Draw("P");
			l4->AddEntry(exQE_R1, Form("Kin5.0 HRS-R"),"p");
		}
	}
	if(N_QE_R2>1){
		TGraphErrors *exQE_R2 = new TGraphErrors(N_QE_R2,xbj_QE_R2, R_EX_QE_R2, Zero,R_EX_Err_QE_R2);
		exQE_R2->SetMarkerStyle(27);
		exQE_R2->SetMarkerSize(1.5);
		exQE_R2->SetMarkerColor(6);
		exQE_R2->SetLineColor(6);
		if(!(Target=="H2")){
			exQE_R2->Draw("P");
			l4->AddEntry(exQE_R2, Form("Kin5.05 HRS-R"),"p");
		}
	}

	if(N_25_L1>1){
		TGraphErrors *ex25_L1 = new TGraphErrors(N_25_L1,xbj_25_L1, R_EX_25_L1, Zero,R_EX_Err_25_L1);
		ex25_L1->SetMarkerStyle(20);
		ex25_L1->SetMarkerSize(1.5);
		ex25_L1->SetMarkerColor(1);
		ex25_L1->SetLineColor(1);
		ex25_L1->Draw("P");
		l4->AddEntry(ex25_L1, Form("Kin5.1 on HRS-L"),"p");
	}
	if(N_25_L2>1){
		TGraphErrors *ex25_L2 = new TGraphErrors(N_25_L2,xbj_25_L2, R_EX_25_L2, Zero,R_EX_Err_25_L2);
		ex25_L2->SetMarkerStyle(21);
		ex25_L2->SetMarkerSize(1.5);
		ex25_L2->SetMarkerColor(2);
		ex25_L2->SetLineColor(2);
		ex25_L2->Draw("P");
		l4->AddEntry(ex25_L2, Form("Kin5.2 on HRS-L"),"p");
	}
	if(N_25_R1>1){
		TGraphErrors *ex25_R1 = new TGraphErrors(N_25_R1,xbj_25_R1, R_EX_25_R1, Zero,R_EX_Err_25_R1);
		ex25_R1->SetMarkerStyle(22);
		ex25_R1->SetMarkerSize(1.5);
		ex25_R1->SetMarkerColor(4);
		ex25_R1->SetLineColor(4);
		ex25_R1->Draw("P");
		l4->AddEntry(ex25_R1, Form("Kin5.1 on HRS-R"),"p");
	}
	if(N_25_R2>1){
		TGraphErrors *ex25_R2 = new TGraphErrors(N_25_R2,xbj_25_R2, R_EX_25_R2, Zero,R_EX_Err_25_R2);
		ex25_R2->SetMarkerStyle(23);
		ex25_R2->SetMarkerSize(1.5);
		ex25_R2->SetMarkerColor(6);
		ex25_R2->SetLineColor(6);
		ex25_R2->Draw("P");
		l4->AddEntry(ex25_R2, Form("Kin5.2 on HRS-R"),"p");
	}
	l4->Draw();
	c3->Print(Form("./kin/A%d_%s_%s_Ratio_%s_%s.png",Theta,Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	c3->Print(Form("./kin/A%d_%s_%s_Ratio_%s_%s.pdf",Theta,Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
		/*}}}*/

	/*Degree 28{{{*/
	TLegend *l5 = new TLegend(lx_min,0.60,lx_max, 0.94,Form("#sigma_{%s} / #sigma_{%s} Ratio: ",Target0.Data(),Target.Data()));
	l5->SetTextSize(0.043);
	l5->SetTextFont(32);

	c3->cd(); c3->Clear(); h3->Draw(); Theta = 28;
	if(N_28_L1>1){
		TGraphErrors *ex28_L1 = new TGraphErrors(N_28_L1,xbj_28_L1, R_EX_28_L1, Zero,R_EX_Err_28_L1);
		ex28_L1->SetMarkerStyle(20);
		ex28_L1->SetMarkerSize(1.9);
		ex28_L1->SetMarkerColor(1);
		ex28_L1->SetLineColor(1);
		if((Target0=="C12" && Target=="He3")||(Target=="C12" && Target0=="He3")){
			ex28_L1->Draw("P");
			l5->AddEntry(ex28_L1, Form("Kin6.5 on HRS-L"),"p");
		}
	}
	if(N_28_L2>1){
		TGraphErrors *ex28_L2 = new TGraphErrors(N_28_L2,xbj_28_L2, R_EX_28_L2, Zero,R_EX_Err_28_L2);
		ex28_L2->SetMarkerStyle(21);
		ex28_L2->SetMarkerSize(1.9);
		ex28_L2->SetMarkerColor(2);
		ex28_L2->SetLineColor(2);
		if((Target0=="C12" && Target=="He3")||(Target=="C12" && Target0=="He3")){
			ex28_L2->Draw("P");
			l5->AddEntry(ex28_L2, Form("Kin6.5 on HRS-L"),"p");
		}
	}
	if(N_28_R2>1){
		TGraphErrors *ex28_R2 = new TGraphErrors(N_28_R2,xbj_28_R2, R_EX_28_R2, Zero,R_EX_Err_28_R2);
		ex28_R2->SetMarkerStyle(21);
		ex28_R2->SetMarkerSize(1.9);
		ex28_R2->SetMarkerColor(2);
		ex28_R2->SetLineColor(2);
		if((Target0=="C12" && Target=="He3")||(Target=="C12" && Target0=="He3")){
			ex28_R2->Draw("P");
			l5->AddEntry(ex28_R2, Form("Kin6.5 on HRS-R"),"p");
		}
	}
	l5->Draw();
	if((Target0=="C12" && Target=="He3")||(Target=="C12" && Target0=="He3")){
		c3->Print(Form("./kin/A%d_%s_%s_Ratio_%s_%s.png",Theta,Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
		c3->Print(Form("./kin/A%d_%s_%s_Ratio_%s_%s.pdf",Theta,Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
	}	
	/*}}}*/

	/*}}}*/
	return 0;
}
/*}}}*/

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

/*Merge{{{*/
void Merge(const TString& aInputFileName,
		double* aXbj_L1, double* aR_EX_L1, double* aR_EX_Err_L1, double* aR_MC_L1, int* aN_L1,
		double* aXbj_L2, double* aR_EX_L2, double* aR_EX_Err_L2, double* aR_MC_L2, int* aN_L2,
		double* aXbj_R1, double* aR_EX_R1, double* aR_EX_Err_R1, double* aR_MC_R1, int* aN_R1,
		double* aXbj_R2, double* aR_EX_R2, double* aR_EX_Err_R2, double* aR_MC_R2, int* aN_R2
		){

	/*Pre-define{{{*/	
	int aline = 0;
	TString aInputFilePath = "/work/halla/e08014/disk1/yez/Xbj_Cross_Section/results/";

	double scale = 1.0;
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
	outlog0<<endl<<"------------------- First Target ----------------------------------------------------------"<<endl<<endl;

	/*Define{{{*/
	Double_t XS_T1L1[200], XS_StatErr_T1L1[200], XS_SystErr_T1L1[200], Ep_T1L1[200], Xbj_T1L1[200],  Xbj_Err_T1L1[200],XS_MC_T1L1[200];
	Double_t XS_T1L2[200], XS_StatErr_T1L2[200], XS_SystErr_T1L2[200], Ep_T1L2[200], Xbj_T1L2[200],  Xbj_Err_T1L2[200],XS_MC_T1L2[200];
	Double_t XS_T1R1[200], XS_StatErr_T1R1[200], XS_SystErr_T1R1[200], Ep_T1R1[200], Xbj_T1R1[200],  Xbj_Err_T1R1[200],XS_MC_T1R1[200];
	Double_t XS_T1R2[200], XS_StatErr_T1R2[200], XS_SystErr_T1R2[200], Ep_T1R2[200], Xbj_T1R2[200],  Xbj_Err_T1R2[200],XS_MC_T1R2[200];
	/*}}}*/

	/*First{{{*/
	Target = gGet_Target_Name(aName_T1L1.Data());
	TString Target1 = Target;

	TString infile_T1L1 = aInputFilePath +Target+"/"+Com0+"/"+ aName_T1L1 +"_"+ Com0;
	outlog0<<"==== Reading 1st file from "<<infile_T1L1<<endl;
	ifstream run_T1L1; run_T1L1.open(infile_T1L1);

	Int_t Count_T1L1 =0;
	if(Target=="He4")
		scale = He4_Norm;
	else
		scale = 1.0;

	Kin = gGet_Kin_Name(infile_T1L1.Data());

	if(Kin=="MM"){
		outlog0<<"1st: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
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
		outlog0<<"*** ERROR, unknown kinematics setting!"<<endl;

	TString Kin0 = Kin;
	TString Arm_T1L1="X";
	if(aName_T1L1.Contains("L_"))
		Arm_T1L1="L";
	else if(aName_T1L1.Contains("R_"))
		Arm_T1L1="R";

	TString KinName_T1L1 = Form("Kin%s",Kin.Data());
	gGet_Xbj_Cut(KinName_T1L1.Data(), Arm_T1L1.Data(),&Xbj_Min, &Xbj_Max);
	outlog0<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T1L1.Data(), Xbj_Min,Xbj_Max)<<endl;

	Get_XS* xs_T1L1 = new Get_XS();
	xs_T1L1->Load_Table(Target.Data(),KinName_T1L1.Data());

	double T1L1_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T1L1.Data(),Theta);
	comment.ReadLine(run_T1L1);
	while ( run_T1L1>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
	{
		if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5&&xbj<=3.00 && XS>0.0 && sqrt(pow(XS_Syst_Err,2.)+pow(XS_Stat_Err,2.))/XS <0.2)
		{
			Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2.);
			Ep_T1L1[Count_T1L1] = Ep; 
			XS_T1L1[Count_T1L1] = XS * scale; 
			XS_StatErr_T1L1[Count_T1L1] = XS_Stat_Err;
			XS_SystErr_T1L1[Count_T1L1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.));
			//XS_SystErr_T1L1[Count_T1L1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.)+pow(Ntg_Syst_Err/Ntg,2.));
			Xbj_T1L1[Count_T1L1] = xbj;    Xbj_Err_T1L1[Count_T1L1] = 0.0;
			XS_MC_T1L1[Count_T1L1] = xs_T1L1->gGet_XS_Born(E0,Ep,Theta);

			if(bPrintMore)
				outlog0<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_MC=%10.6e",Target.Data(),
						KinName_T1L1.Data(), Ep_T1L1[Count_T1L1], Xbj_T1L1[Count_T1L1], 
					XS_T1L1[Count_T1L1],XS_MC_T1L1[Count_T1L1])<<endl;

			Count_T1L1++;
		}
		if ( !run_T1L1.good() )
			break;
	}
	run_T1L1.close();
	delete xs_T1L1;
	outlog0 << "  Total XS Points for 1st = " << Count_T1L1 <<endl;
	/*}}}*/

	/*Second{{{*/
	TString KinName_T1L2 ="";
	Bool_t bMore_T1L2 = kTRUE;
	TString infile_T1L2 = aInputFilePath +Target+"/"+Com0+"/"+  aName_T1L2 +"_"+ Com0;
	outlog0<<"==== Reading 2nd file from "<<infile_T1L2<<endl;
	TString Arm_T1L2="X";
	if(aName_T1L2 =="0")
		bMore_T1L2 = kFALSE;
	if(aName_T1L2.Contains("L_"))
		Arm_T1L2="L";
	else if(aName_T1L2.Contains("R_"))
		Arm_T1L2="R";

	double T1L2_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T1L2.Data(),Theta);
	Int_t Count_T1L2=0;
	if(bMore_T1L2){
		ifstream run_T1L2; run_T1L2.open(infile_T1L2);
		Target = gGet_Target_Name(infile_T1L2.Data());
		if(Target=="He4")
			scale = He4_Norm;
		else
			scale = 1.0;

		Kin = gGet_Kin_Name(infile_T1L2.Data());
		if(Kin=="MM"){
			outlog0<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
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
			outlog0<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T1L2 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T1L2.Data(), Arm_T1L2.Data(),&Xbj_Min, &Xbj_Max);
		outlog0<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T1L2.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T1L2 = new Get_XS();
		xs_T1L2->Load_Table(Target.Data(),KinName_T1L2.Data());

		comment.ReadLine(run_T1L2);
		while ( run_T1L2>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5 &&xbj<=3.00  && XS>0.0 && sqrt(pow(XS_Syst_Err,2.)+pow(XS_Stat_Err,2.))/XS <0.2)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2.);
				Ep_T1L2[Count_T1L2] = Ep; 
				XS_T1L2[Count_T1L2] = XS * scale;    
				XS_StatErr_T1L2[Count_T1L2] = XS_Stat_Err;
				XS_SystErr_T1L2[Count_T1L2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.));
				//XS_SystErr_T1L2[Count_T1L2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.)+pow(Ntg_Syst_Err/Ntg,2.));
				Xbj_T1L2[Count_T1L2] = xbj;    Xbj_Err_T1L2[Count_T1L2] = 0.0;
				XS_MC_T1L2[Count_T1L2] = xs_T1L2->gGet_XS_Born(E0,Ep,Theta);

			if(bPrintMore)
				outlog0<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_MC=%10.6e",Target.Data(),
						KinName_T1L2.Data(), Ep_T1L2[Count_T1L2], Xbj_T1L2[Count_T1L2], 
						XS_T1L2[Count_T1L2],XS_MC_T1L2[Count_T1L2])<<endl;

				Count_T1L2++;
			}
			if ( !run_T1L2.good() )
				break;
		}
		run_T1L2.close();
		delete xs_T1L2;
		outlog0 << "  Total XS Points for 2nd  = " << Count_T1L2 <<endl;
	}
	/*}}}*/

	/*Third{{{*/
	TString KinName_T1R1 ="";
	Bool_t bMore_T1R1 = kTRUE;
	TString infile_T1R1 =  aInputFilePath +Target+"/"+Com0+"/"+ aName_T1R1 +"_"+ Com0;
	outlog0<<"==== Reading 3rd file from "<<infile_T1R1<<endl;
	TString Arm_T1R1="X";
	if(aName_T1R1 =="0")
		bMore_T1R1 = kFALSE;
	if(aName_T1R1.Contains("L_"))
		Arm_T1R1="L";
	else if(aName_T1R1.Contains("R_"))
		Arm_T1R1="R";

	double T1R1_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T1R1.Data(),Theta);
	Int_t Count_T1R1=0;
	if(bMore_T1R1){
		ifstream run_T1R1; run_T1R1.open(infile_T1R1);
		Target = gGet_Target_Name(infile_T1R1.Data());
		if(Target=="He4")
			scale = He4_Norm;
		else
			scale = 1.0;

		Kin = gGet_Kin_Name(infile_T1R1.Data());
		if(Kin=="MM"){
			outlog0<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
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
			outlog0<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T1R1 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T1R1.Data(), Arm_T1R1.Data(),&Xbj_Min, &Xbj_Max);
		outlog0<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T1R1.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T1R1 = new Get_XS();
		xs_T1R1->Load_Table(Target.Data(),KinName_T1R1.Data());

		comment.ReadLine(run_T1R1);
		while ( run_T1R1>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5 &&xbj<=3.00  && XS>0.0 && sqrt(pow(XS_Syst_Err,2.)+pow(XS_Stat_Err,2.))/XS <0.2)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2.);
				Ep_T1R1[Count_T1R1] = Ep; 
				XS_T1R1[Count_T1R1] = XS * scale; 
				XS_StatErr_T1R1[Count_T1R1] = XS_Stat_Err;
				XS_SystErr_T1R1[Count_T1R1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.));
				//XS_SystErr_T1R1[Count_T1R1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.)+pow(Ntg_Syst_Err/Ntg,2.));
				Xbj_T1R1[Count_T1R1] = xbj;    Xbj_Err_T1R1[Count_T1R1] = 0.0;
				XS_MC_T1R1[Count_T1R1] = xs_T1R1->gGet_XS_Born(E0,Ep,Theta);

				if(bPrintMore)
					outlog0<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_MC=%10.6e",Target.Data(),
						KinName_T1R1.Data(), Ep_T1R1[Count_T1R1], Xbj_T1R1[Count_T1R1], 
						XS_T1R1[Count_T1R1],XS_MC_T1R1[Count_T1R1])<<endl;

				Count_T1R1++;
			}
			if ( !run_T1R1.good() )
				break;
		}
		run_T1R1.close();
		delete xs_T1R1;
		outlog0 << "  Total XS Points for 2nd  = " << Count_T1R1 <<endl;
	}
	/*}}}*/

	/*Forth{{{*/
	TString KinName_T1R2 ="";
	Bool_t bMore_T1R2 = kTRUE;
	TString infile_T1R2 = aInputFilePath +Target+"/"+Com0+"/"+  aName_T1R2 +"_"+ Com0;
	outlog0<<"==== Reading 4th file from "<<infile_T1R2<<endl;
	TString Arm_T1R2="X";
	if(aName_T1R2 =="0")
		bMore_T1R2 = kFALSE;
	if(aName_T1R2.Contains("L_"))
		Arm_T1R2="L";
	else if(aName_T1R2.Contains("R_"))
		Arm_T1R2="R";

	double T1R2_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T1R2.Data(),Theta);
	Int_t Count_T1R2=0;
	if(bMore_T1R2){
		ifstream run_T1R2; run_T1R2.open(infile_T1R2);
		Target = gGet_Target_Name(infile_T1R2.Data());
		if(Target=="He4")
			scale = He4_Norm;
		else
			scale = 1.0;

		Kin = gGet_Kin_Name(infile_T1R2.Data());
		if(Kin=="MM"){
			outlog0<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
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
			outlog0<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T1R2 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T1R2.Data(), Arm_T1R2.Data(),&Xbj_Min, &Xbj_Max);
		outlog0<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T1R2.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T1R2 = new Get_XS();
		xs_T1R2->Load_Table(Target.Data(),KinName_T1R2.Data());

		comment.ReadLine(run_T1R2);
		while ( run_T1R2>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5  &&xbj<=3.00 && XS>0.0 && sqrt(pow(XS_Syst_Err,2.)+pow(XS_Stat_Err,2.))/XS <0.2)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2.);
				Ep_T1R2[Count_T1R2] = Ep; 
				XS_T1R2[Count_T1R2] = XS * scale;
				XS_StatErr_T1R2[Count_T1R2] = XS_Stat_Err;
				XS_SystErr_T1R2[Count_T1R2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.));
				//XS_SystErr_T1R2[Count_T1R2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.)+pow(Ntg_Syst_Err/Ntg,2.));
				Xbj_T1R2[Count_T1R2] = xbj;    Xbj_Err_T1R2[Count_T1R2] = 0.0;
				XS_MC_T1R2[Count_T1R2] = xs_T1R2->gGet_XS_Born(E0,Ep,Theta);

				if(bPrintMore)
				outlog0<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_MC=%10.6e",Target.Data(),
						KinName_T1R2.Data(), Ep_T1R2[Count_T1R2], Xbj_T1R2[Count_T1R2], 
						XS_T1R2[Count_T1R2],XS_MC_T1R2[Count_T1R2])<<endl;

				Count_T1R2++;
			}
			if ( !run_T1R2.good() )
				break;
		}
		run_T1R2.close();
		delete xs_T1R2;
		outlog0 << "  Total XS Points for 2nd  = " << Count_T1R2 <<endl;
	}
	/*}}}*/
	/*}}}*/

	/*Second Target{{{*/
	outlog0<<endl<<"------------------ Second Target ----------------------------------------------------------"<<endl<<endl;

	/*Define{{{*/
	Double_t XS_T2L1[200], XS_SystErr_T2L1[200], XS_StatErr_T2L1[200], Ep_T2L1[200], Xbj_T2L1[200],  Xbj_Err_T2L1[200],XS_MC_T2L1[200];
	Double_t XS_T2L2[200], XS_SystErr_T2L2[200], XS_StatErr_T2L2[200], Ep_T2L2[200], Xbj_T2L2[200],  Xbj_Err_T2L2[200],XS_MC_T2L2[200];
	Double_t XS_T2R1[200], XS_SystErr_T2R1[200], XS_StatErr_T2R1[200], Ep_T2R1[200], Xbj_T2R1[200],  Xbj_Err_T2R1[200],XS_MC_T2R1[200];
	Double_t XS_T2R2[200], XS_SystErr_T2R2[200], XS_StatErr_T2R2[200], Ep_T2R2[200], Xbj_T2R2[200],  Xbj_Err_T2R2[200],XS_MC_T2R2[200];
	/*}}}*/

	/*First{{{*/
	Target = gGet_Target_Name(aName_T2L1.Data());
	TString Target2 = Target;

	TString infile_T2L1 = aInputFilePath +Target+"/"+Com+"/"+  aName_T2L1 +"_"+ Com;
	outlog0<<"==== Reading 1st file from "<<infile_T2L1<<endl;
	ifstream run_T2L1; run_T2L1.open(infile_T2L1);

	Int_t Count_T2L1 =0;
	if(Target=="He4")
		scale = He4_Norm;
	else
		scale = 1.0;

	Kin = gGet_Kin_Name(infile_T2L1.Data());

	TString Arm_T2L1="X";
	if(aName_T2L1.Contains("L_"))
		Arm_T2L1="L";
	else if(aName_T2L1.Contains("R_"))
		Arm_T2L1="R";


	if(Kin=="MM"){
		outlog0<<"1st: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
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
		outlog0<<"*** ERROR, unknown kinematics setting!"<<endl;

	TString KinName_T2L1 = Form("Kin%s",Kin.Data());
	gGet_Xbj_Cut(KinName_T2L1.Data(), Arm_T2L1.Data(),&Xbj_Min, &Xbj_Max);
	outlog0<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T2L1.Data(), Xbj_Min,Xbj_Max)<<endl;

	Get_XS* xs_T2L1 = new Get_XS();
	xs_T2L1->Load_Table(Target.Data(),KinName_T2L1.Data());

	double T2L1_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T2L1.Data(),Theta);
	comment.ReadLine(run_T2L1);
	while ( run_T2L1>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
	{
		if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Syst_Err,2.)+pow(XS_Stat_Err,2.))/XS <0.2)
		{
			Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2.);
			Ep_T2L1[Count_T2L1]=Ep;
			XS_T2L1[Count_T2L1] = XS * scale;
			XS_StatErr_T2L1[Count_T2L1] = XS_Stat_Err;
			XS_SystErr_T2L1[Count_T2L1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.));
			//XS_SystErr_T2L1[Count_T2L1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.)+pow(Ntg_Syst_Err/Ntg,2.));
			Xbj_T2L1[Count_T2L1] = xbj;    Xbj_Err_T2L1[Count_T2L1] = 0.0;
			XS_MC_T2L1[Count_T2L1] = xs_T2L1->gGet_XS_Born(E0,Ep,Theta);

			if(bPrintMore)
				outlog0<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_MC=%10.6e",Target.Data(),
					KinName_T2L1.Data(), Ep_T2L1[Count_T2L1], Xbj_T2L1[Count_T2L1], 
					XS_T2L1[Count_T2L1],XS_MC_T2L1[Count_T2L1])<<endl;

			Count_T2L1++;
		}
		if ( !run_T2L1.good() )
			break;
	}
	run_T2L1.close();
	delete xs_T2L1;
	outlog0 << "  Total XS Points for 1st = " << Count_T2L1 <<endl;
	/*}}}*/

	/*Second{{{*/
	TString KinName_T2L2 ="";
	Bool_t bMore_T2L2 = kTRUE;
	TString infile_T2L2 = aInputFilePath +Target+"/"+Com+"/"+  aName_T2L2 +"_"+ Com;
	outlog0<<"==== Reading 2nd file from "<<infile_T2L2<<endl;
	TString Arm_T2L2="X";
	if(aName_T2L2 =="0")
		bMore_T2L2 = kFALSE;
	if(aName_T2L2.Contains("L_"))
		Arm_T2L2="L";
	else if(aName_T2L2.Contains("R_"))
		Arm_T2L2="R";

	double T2L2_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T2L2.Data(),Theta);
	Int_t Count_T2L2=0;
	if(bMore_T2L2){
		ifstream run_T2L2; run_T2L2.open(infile_T2L2);
		Target = gGet_Target_Name(infile_T2L2.Data());
		if(Target=="He4")
			scale = He4_Norm;
		else
			scale = 1.0;

		Kin = gGet_Kin_Name(infile_T2L2.Data());
		if(Kin=="MM"){
			outlog0<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
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
			outlog0<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T2L2 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T2L2.Data(), Arm_T2L2.Data(),&Xbj_Min, &Xbj_Max);
		outlog0<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T2L2.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T2L2 = new Get_XS();
		xs_T2L2->Load_Table(Target.Data(),KinName_T2L2.Data());

		comment.ReadLine(run_T2L2);
		while ( run_T2L2>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Syst_Err,2.)+pow(XS_Stat_Err,2.))/XS <0.2)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2.);
				Ep_T2L2[Count_T2L2]=Ep;
				XS_T2L2[Count_T2L2] = XS * scale; 
				XS_StatErr_T2L2[Count_T2L2] = XS_Stat_Err;
				XS_SystErr_T2L2[Count_T2L2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.));
				//XS_SystErr_T2L2[Count_T2L2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.)+pow(Ntg_Syst_Err/Ntg,2.));
				Xbj_T2L2[Count_T2L2] = xbj;    Xbj_Err_T2L2[Count_T2L2] = 0.0;
				XS_MC_T2L2[Count_T2L2] = xs_T2L2->gGet_XS_Born(E0,Ep,Theta);

			if(bPrintMore)
				outlog0<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_MC=%10.6e",Target.Data(),
						KinName_T2L2.Data(), Ep_T2L2[Count_T2L2], Xbj_T2L2[Count_T2L2], 
						XS_T2L2[Count_T2L2],XS_MC_T2L2[Count_T2L2])<<endl;

				Count_T2L2++;
			}
			if ( !run_T2L2.good() )
				break;
		}
		run_T2L2.close();
		delete xs_T2L2;
		outlog0 << "  Total XS Points for 2nd  = " << Count_T2L2 <<endl;
	}
	/*}}}*/

	/*Third{{{*/
	TString KinName_T2R1 ="";
	Bool_t bMore_T2R1 = kTRUE;
	TString infile_T2R1 = aInputFilePath +Target+"/"+Com+"/"+  aName_T2R1 +"_"+ Com;
	outlog0<<"==== Reading 3rd file from "<<infile_T2R1<<endl;
	TString Arm_T2R1="X";
	if(aName_T2R1 =="0")
		bMore_T2R1 = kFALSE;
	if(aName_T2R1.Contains("L_"))
		Arm_T2R1="L";
	else if(aName_T2R1.Contains("R_"))
		Arm_T2R1="R";

	double T2R1_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T2R1.Data(),Theta);
	Int_t Count_T2R1=0;
	if(bMore_T2R1){
		ifstream run_T2R1; run_T2R1.open(infile_T2R1);
		Target = gGet_Target_Name(infile_T2R1.Data());
		if(Target=="He4")
			scale = He4_Norm;
		else
			scale = 1.0;

		Kin = gGet_Kin_Name(infile_T2R1.Data());
		if(Kin=="MM"){
			outlog0<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
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
			outlog0<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T2R1 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T2R1.Data(), Arm_T2R1.Data(),&Xbj_Min, &Xbj_Max);
		outlog0<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T2R1.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T2R1 = new Get_XS();
		xs_T2R1->Load_Table(Target.Data(),KinName_T2R1.Data());

		comment.ReadLine(run_T2R1);
		while ( run_T2R1>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Syst_Err,2.)+pow(XS_Stat_Err,2.))/XS <0.2)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2.);
				Ep_T2R1[Count_T2R1]=Ep;
				XS_T2R1[Count_T2R1] = XS* scale;   
				XS_StatErr_T2R1[Count_T2R1] = XS_Stat_Err;
				XS_SystErr_T2R1[Count_T2R1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.));
				//XS_SystErr_T2R1[Count_T2R1] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.)+pow(Ntg_Syst_Err/Ntg,2.));
				Xbj_T2R1[Count_T2R1] = xbj;    Xbj_Err_T2R1[Count_T2R1] = 0.0;
				XS_MC_T2R1[Count_T2R1] = xs_T2R1->gGet_XS_Born(E0,Ep,Theta);

			if(bPrintMore)
				outlog0<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_MC=%10.6e",Target.Data(),
						KinName_T2R1.Data(), Ep_T2R1[Count_T2R1], Xbj_T2R1[Count_T2R1], 
						XS_T2R1[Count_T2R1],XS_MC_T2R1[Count_T2R1])<<endl;

				Count_T2R1++;
			}
			if ( !run_T2R1.good() )
				break;
		}
		run_T2R1.close();
		delete xs_T2R1;
		outlog0 << "  Total XS Points for 2nd  = " << Count_T2R1 <<endl;
	}
	/*}}}*/

	/*Forth{{{*/
	TString KinName_T2R2 ="";
	Bool_t bMore_T2R2 = kTRUE;
	TString infile_T2R2 = aInputFilePath +Target+"/"+Com+"/"+ aName_T2R2 +"_"+ Com;
	outlog0<<"==== Reading 4th file from "<<infile_T2R2<<endl;
	TString Arm_T2R2="X";
	if(aName_T2R2 =="0")
		bMore_T2R2 = kFALSE;
	if(aName_T2R2.Contains("L_"))
		Arm_T2R2="L";
	else if(aName_T2R2.Contains("R_"))
		Arm_T2R2="R";

	double T2R2_Syst_Err = gGet_Total_SystErr(Target.Data(), Arm_T2R2.Data(),Theta);
	Int_t Count_T2R2=0;
	if(bMore_T2R2){
		ifstream run_T2R2; run_T2R2.open(infile_T2R2);
		Target = gGet_Target_Name(infile_T2R2.Data());
		if(Target=="He4")
			scale = He4_Norm;
		else
			scale = 1.0;

		Kin = gGet_Kin_Name(infile_T2R2.Data());
		if(Kin=="MM"){
			outlog0<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
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
			outlog0<<"*** ERROR, unknown kinematics setting!"<<endl;
		KinName_T2R2 = Form("Kin%s",Kin.Data());
		gGet_Xbj_Cut(KinName_T2R2.Data(), Arm_T2R2.Data(),&Xbj_Min, &Xbj_Max);
		outlog0<<Form("@@@  For %s, Xbj_Min = %f, Xbj_Max = %f", KinName_T2R2.Data(), Xbj_Min,Xbj_Max)<<endl;

		Get_XS* xs_T2R2 = new Get_XS();
		xs_T2R2->Load_Table(Target.Data(),KinName_T2R2.Data());

		comment.ReadLine(run_T2R2);
		while ( run_T2R2>>XS>>XS_Stat_Err>>XS_Syst_Err>>XS_MC>>xbj>>angle>>Ep>>nu>>Q2>>BinCor>>Livetime>>LT_Syst_Err>>Ntg>>Ntg_Syst_Err>>Ni>>Ni_Syst_Err>>Nf_EX>>Nf_AL>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Syst_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Syst_Err>>Yield_AL>>Y_AL_Stat_Err>>Y_AL_Syst_Err )
		{
			if ( xbj>=Xbj_Min && xbj<=Xbj_Max && angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Syst_Err,2.)+pow(XS_Stat_Err,2.))/XS <0.2)
			{
				Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2.);
				Ep_T2R2[Count_T2R2]=Ep;
				XS_T2R2[Count_T2R2] = XS * scale;     
				XS_StatErr_T2R2[Count_T2R2] = XS_Stat_Err;
				XS_SystErr_T2R2[Count_T2R2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.));
				//XS_SystErr_T2R2[Count_T2R2] = XS*sqrt(pow(LT_Syst_Err/Livetime,2.)+pow(Ni_Syst_Err/Ni,2.)+pow(Ntg_Syst_Err/Ntg,2.));
				Xbj_T2R2[Count_T2R2] = xbj;    Xbj_Err_T2R2[Count_T2R2] = 0.0;
				XS_MC_T2R2[Count_T2R2] = xs_T2R2->gGet_XS_Born(E0,Ep,Theta);

			if(bPrintMore)
				outlog0<<Form("%s at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_MC=%10.6e",Target.Data(),
						KinName_T2R2.Data(), Ep_T2R2[Count_T2R2], Xbj_T2R2[Count_T2R2], 
						XS_T2R2[Count_T2R2],XS_MC_T2R2[Count_T2R2])<<endl;

				Count_T2R2++;
			}
			if ( !run_T2R2.good() )
				break;
		}
		run_T2R2.close();
		delete xs_T2R2;
		outlog0 << "  Total XS Points for 2nd  = " << Count_T2R2 <<endl;
	}
	/*}}}*/
	/*}}}*/

	/*Ratio T1L1{{{*/  
	double T1_Syst_Err_Com = T1L1_Syst_Err;
	double T2_Syst_Err_Com = T2L1_Syst_Err;
	double Ratio_Syst_Err = gGet_Ratio_SystErr(Target1.Data(),Target2.Data());
	Double_t ratio,ratio_mc,err;

	outlog0 << "========= First Kin =======" <<endl;	
	if(Count_T1L1>1&& Count_T2L1>1){
		Int_t Count_L1=0;
		int i,j; 
		for( i=0;i<Count_T1L1;i++){
			if(bPrintMore)
				outlog0<<Form("#1 at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_StatErr=%10.6e, XS_SystErr=%10.6e",
						KinName_T1L1.Data(), Ep_T1L1[i], Xbj_T1L1[i], 
						XS_T1L1[i],XS_StatErr_T1L1[i],XS_SystErr_T1L1[i])<<endl;
		}
		for( j=0;j<Count_T2L1;j++){
			if(bPrintMore)
				outlog0<<Form("#2 at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_StatErr=%10.6e, XS_SystErr=%10.6e",
						KinName_T2L1.Data(), Ep_T2L1[j], Xbj_T2L1[j], 
						XS_T2L1[j],XS_StatErr_T2L1[j],XS_SystErr_T2L1[j])<<endl;
			}
		for( i=0;i<Count_T1L1;i++){
			for( j=0;j<Count_T2L1;j++){
				if(Xbj_T1L1[i]>=0.8&&Xbj_T2L1[j]>=0.8&&fabs(Xbj_T1L1[i]-Xbj_T2L1[j])<0.001){
					ratio = factor*XS_T1L1[i]/XS_T2L1[j];
					double err_total = sqrt( 1./(1./pow(XS_StatErr_T2L1[j]/XS_T2L1[j],2.) 
							+ 1./pow(XS_StatErr_T1L1[i]/XS_T1L1[i],2.))
							+ pow(XS_SystErr_T2L1[j]/XS_T2L1[j],2.)//only stat+LT_sys+Ne_sys
							+ pow(XS_SystErr_T1L1[i]/XS_T1L1[i],2.)//only stat+LT_sys+Ne_sys
							+ pow(Ratio_Syst_Err,2.));//add other comment syst_err that don't cancel
					err = ratio * (err_total);	
							
					outlog0 <<"   T2_StatErr="<< 100.*(XS_StatErr_T2L1[j]/XS_T2L1[j]) 
						<<"   T2_SystErr="<< 100.*(XS_SystErr_T2L1[j]/XS_T2L1[j])//only stat+LT_sys+Ne_sys
						<<"   T1_StatErr="<< 100.*(XS_StatErr_T1L1[i]/XS_T1L1[i])
						<<"   T1_SystErr="<< 100.*(XS_SystErr_T1L1[i]/XS_T1L1[i])//only stat+LT_sys+Ne_sys
						<<"   Ratio_Err="<< 100.*(Ratio_Syst_Err)//add other comment syst_err that don't cancel
						<<"   Total_Err="<< 100.* err_total
						<<endl;
					ratio_mc = factor*XS_MC_T1L1[i]/XS_MC_T2L1[j];
					//	if(ratio>1e-30 && ratio<1000.){
					//if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
					aXbj_L1[Count_L1] = Xbj_T1L1[i];
					aR_EX_L1[Count_L1] = ratio;
					aR_EX_Err_L1[Count_L1] = err;
					aR_MC_L1[Count_L1] = ratio_mc;
					outlog0<< Form("#%d: xbj=%10.6e, R=%10.6e, R_Err=%10.6e", Count_L1, aXbj_L1[Count_L1], aR_EX_L1[Count_L1], aR_EX_Err_L1[Count_L1])<<endl;
					Count_L1++;
					//	}
				}
				}
			}
			aN_L1[0] = Count_L1;
		}

		outlog0<<"******************** Factor = "<< factor<<endl;
		/*}}}*/

	/*Ratio T1L2{{{*/ 
	outlog0 << "========= Second Kin =======" <<endl;	
	if(Count_T1L2>1&& Count_T2L2>1){
		Int_t Count_L2=0;
		int i,j; 
		for( i=0;i<Count_T1L2;i++){
			if(bPrintMore)
				outlog0<<Form("#1 at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_StatErr=%10.6e, XS_SystErr=%10.6e",
						KinName_T1L2.Data(), Ep_T1L2[i], Xbj_T1L2[i], 
						XS_T1L2[i],XS_StatErr_T1L2[i],XS_SystErr_T1L2[i])<<endl;
		}
		for( j=0;j<Count_T2L1;j++){
			if(bPrintMore)
				outlog0<<Form("#2 at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_StatErr=%10.6e, XS_SystErr=%10.6e",
						KinName_T2L2.Data(), Ep_T2L2[j], Xbj_T2L2[j], 
						XS_T2L2[j],XS_StatErr_T2L2[j],XS_SystErr_T2L2[j])<<endl;
		}
		for( i=0;i<Count_T1L2;i++){
			for( j=0;j<Count_T2L2;j++){
				if(Xbj_T1L2[i]>=0.8&&Xbj_T2L2[j]>=0.8&&fabs(Xbj_T1L2[i]-Xbj_T2L2[j])<0.001){
					ratio = factor*XS_T1L2[i]/XS_T2L2[j];
					double err_total = sqrt( 1./(1./pow(XS_StatErr_T2L2[j]/XS_T2L2[j],2.) 
							+ 1.0/pow(XS_StatErr_T1L2[i]/XS_T1L2[i],2.))
							+ pow(XS_SystErr_T2L2[j]/XS_T2L2[j],2.)//only stat+LT_sys+Ne_sys
							+ pow(XS_SystErr_T1L2[i]/XS_T1L2[i],2.)//only stat+LT_sys+Ne_sys
							+ pow(Ratio_Syst_Err,2.));//add other comment syst_err that don't cancel
					err = ratio * (err_total);	

					outlog0 <<"   T2_StatErr="<< 100.*(XS_StatErr_T2L2[j]/XS_T2L2[j]) 
						<<"   T2_SystErr="<< 100.*(XS_SystErr_T2L2[j]/XS_T2L2[j])//only stat+LT_sys+Ne_sys
						<<"   T1_StatErr="<< 100.*(XS_StatErr_T1L2[i]/XS_T1L2[i])
						<<"   T1_SystErr="<< 100.*(XS_SystErr_T1L2[i]/XS_T1L2[i])//only stat+LT_sys+Ne_sys
						<<"   Ratio_Err="<< 100.*(Ratio_Syst_Err)//add other comment syst_err that don't cancel
						<<"   Total_Err="<< 100.* err_total
						<<endl;
						ratio_mc = factor*XS_MC_T1L2[i]/XS_MC_T2L2[j];
					//if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
						aXbj_L2[Count_L2] = Xbj_T1L2[i];
						aR_EX_L2[Count_L2] = ratio;
						aR_EX_Err_L2[Count_L2] = err;
						aR_MC_L2[Count_L2] = ratio_mc;
						outlog0<< Form("#%d: xbj=%10.6e, R=%10.6e, R_Err=%10.6e", Count_L2, aXbj_L2[Count_L2], aR_EX_L2[Count_L2], aR_EX_Err_L2[Count_L2])<<endl;
						Count_L2++;
					//}
				}
			}
		}
		aN_L2[0] = Count_L2;
	}


	outlog0<<"******************** Factor = "<< factor<<endl;
	/*}}}*/

	/*Ratio T1R1{{{*/  
    outlog0 << "========= Third Kin =======" <<endl;	
	if(Count_T1R1>1&& Count_T2R1>1){
		Int_t Count_R1=0;
		int i,j; 
		for( i=0;i<Count_T1R1;i++){
			if(bPrintMore)
				outlog0<<Form("#1 at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_StatErr=%10.6e, XS_SystErr=%10.6e",
						KinName_T1R1.Data(), Ep_T1R1[i], Xbj_T1R1[i], 
						XS_T1R1[i],XS_StatErr_T1R1[i],XS_SystErr_T1R1[i])<<endl;
		}
		for( j=0;j<Count_T2R1;j++){
			if(bPrintMore)
				outlog0<<Form("#2 at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_StatErr=%10.6e, XS_SystErr=%10.6e",
						KinName_T2R1.Data(), Ep_T2R1[j], Xbj_T2R1[j], 
						XS_T2R1[j],XS_StatErr_T2R1[j],XS_SystErr_T2R1[j])<<endl;
		}
		for( i=0;i<Count_T1R1;i++){
			for( j=0;j<Count_T2R1;j++){
				if(Xbj_T1R1[i]>=0.8&&Xbj_T2R1[j]>=0.8&&fabs(Xbj_T1R1[i]-Xbj_T2R1[j])<0.001){
					ratio = factor*XS_T1R1[i]/XS_T2R1[j];
					double err_total = sqrt( 1./(1./pow(XS_StatErr_T2R1[j]/XS_T2R1[j],2.) 
							+ 1./pow(XS_StatErr_T1R1[i]/XS_T1R1[i],2.))
							+ pow(XS_SystErr_T2R1[j]/XS_T2R1[j],2.)//only stat+LT_sys+Ne_sys
							+ pow(XS_SystErr_T1R1[i]/XS_T1R1[i],2.)//only stat+LT_sys+Ne_sys
							+ pow(Ratio_Syst_Err,2.));//add other comment syst_err that don't cancel
						err = ratio * (err_total);	
					outlog0 <<"   T2_StatErr="<< 100.*(XS_StatErr_T2R1[j]/XS_T2R1[j]) 
						<<"   T2_SystErr="<< 100.*(XS_SystErr_T2R1[j]/XS_T2R1[j])//only stat+LT_sys+Ne_sys
						<<"   T1_StatErr="<< 100.*(XS_StatErr_T1R1[i]/XS_T1R1[i])
						<<"   T1_SystErr="<< 100.*(XS_SystErr_T1R1[i]/XS_T1R1[i])//only stat+LT_sys+Ne_sys
						<<"   Ratio_Err="<< 100.*(Ratio_Syst_Err)//add other comment syst_err that don't cancel
						<<"   Total_Err="<< 100.* err_total
						<<endl;
		
					ratio_mc = factor*XS_MC_T1R1[i]/XS_MC_T2R1[j];
					//if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
					    aXbj_R1[Count_R1] = Xbj_T1R1[i];
						aR_EX_R1[Count_R1] = ratio;
						aR_EX_Err_R1[Count_R1] = err;
						aR_MC_R1[Count_R1] = ratio_mc;
				        outlog0<< Form("#%d: xbj=%10.6e, R=%10.6e, R_Err=%10.6e", Count_R1, aXbj_R1[Count_R1], aR_EX_R1[Count_R1], aR_EX_Err_R1[Count_R1])<<endl;
						Count_R1++;
					//}
				}
			}
		}
		aN_R1[0] = Count_R1;
	}


	outlog0<<"******************** Factor = "<< factor<<endl;
	/*}}}*/
	
	/*Ratio T1R2{{{*/  
    outlog0 << "========= Four Kin =======" <<endl;	
	if(Count_T1R2>1&& Count_T2R2>1){
		Int_t Count_R2=0;
		int i,j; 
		for( i=0;i<Count_T1R2;i++){
			if(bPrintMore)
				outlog0<<Form("#1 at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_StatErr=%10.6e, XS_SystErr=%10.6e",
						KinName_T1R2.Data(), Ep_T1R2[i], Xbj_T1R2[i], 
						XS_T1R2[i],XS_StatErr_T1R2[i],XS_SystErr_T1R2[i])<<endl;
		}
		for( j=0;j<Count_T2R2;j++){
			if(bPrintMore)
				outlog0<<Form("#2 at %s: Ep = %5.3f, xbj=%5.3f, XS_EX=%10.6e, XS_StatErr=%10.6e, XS_SystErr=%10.6e",
						KinName_T2R2.Data(), Ep_T2R2[j], Xbj_T2R2[j], 
						XS_T2R2[j],XS_StatErr_T2R2[j],XS_SystErr_T2R2[j])<<endl;
		}
		for( i=0;i<Count_T1R2;i++){
			for( j=0;j<Count_T2R2;j++){
				if(Xbj_T1R2[i]>=0.8&&Xbj_T2R2[j]>=0.8&&fabs(Xbj_T1R2[i]-Xbj_T2R2[j])<0.001){
					ratio = factor*XS_T1R2[i]/XS_T2R2[j];
					double err_total = sqrt( 1./(1./pow(XS_StatErr_T2R2[j]/XS_T2R2[j],2.) 
							+ 1./pow(XS_StatErr_T1R2[i]/XS_T1R2[i],2.))
							+ pow(XS_SystErr_T2R2[j]/XS_T2R2[j],2.)//only stat+LT_sys+Ne_sys
							+ pow(XS_SystErr_T1R2[i]/XS_T1R2[i],2.)//only stat+LT_sys+Ne_sys
							+ pow(Ratio_Syst_Err,2.));//add other comment syst_err that don't cancel
						err = ratio * (err_total);	
							
					outlog0 <<"   T2_StatErr="<< 100.*(XS_StatErr_T2R2[j]/XS_T2R2[j]) 
						<<"   T2_SystErr="<< 100.*(XS_SystErr_T2R2[j]/XS_T2R2[j])//only stat+LT_sys+Ne_sys
						<<"   T1_StatErr="<< 100.*(XS_StatErr_T1R2[i]/XS_T1R2[i])
						<<"   T1_SystErr="<< 100.*(XS_SystErr_T1R2[i]/XS_T1R2[i])//only stat+LT_sys+Ne_sys
						<<"   Ratio_Err="<< 100.*(Ratio_Syst_Err)//add other comment syst_err that don't cancel
						<<"   Total_Err="<< 100.* err_total
						<<endl;
			ratio_mc = factor*XS_MC_T1R2[i]/XS_MC_T2R2[j];
					//if(ratio>1e-30 && ratio<1000.&& (err/ratio)<1.0){
						aXbj_R2[Count_R2] = Xbj_T1R2[i];
						aR_EX_R2[Count_R2] = ratio;
						aR_EX_Err_R2[Count_R2] = err;
						aR_MC_R2[Count_R2] = ratio_mc;
						outlog0<< Form("#%d: xbj=%10.6e, R=%10.6e, R_Err=%10.6e", Count_R2, aXbj_R2[Count_R2], aR_EX_R2[Count_R2], aR_EX_Err_R2[Count_R2])<<endl;
						Count_R2++;
					//}
				}
			}
		}
		aN_R2[0] = Count_R2;
	}

	outlog0<<"******************** Factor = "<< factor<<endl;
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
		outlog0<<" **** I don't know this target:  "<<aTarget.Data()<<endl;
		aA[0]=0; aZ[0]=0;
	} 
}
/*}}}*/

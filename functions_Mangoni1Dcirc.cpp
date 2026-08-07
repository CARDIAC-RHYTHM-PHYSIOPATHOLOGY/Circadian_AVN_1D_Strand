#include "Structs_circ.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

////////////////////SET PARAMETERS////////////////////////
void set_parameters_mAVNM_BM(Parameters &p)
{
    // Time step
    p.dt   = 0.01;                // [ms]
    
    // Constants
    p.R    = 8.3144e3;            // [uJ/(mmol K)]
    p.F    = 9.6485e4;            // [mC/mmol]
    p.T    = 310;                 // [K]
    p.FoRT = p.F / ( p.R * p.T ); // [mV^-1]
    
    // Temperature coefficient
    p.Q10  = 0.2378; 		  // [-]
    
    // Capacitance
    p.Cm      = 22;               // [pF]
    p.Cm_surf = 1;                // [uF/cm^2]  
    
    // Stimulus parameters
    p.stimduration = 5;//1;           // [ms]
    p.stimmag      = -0.2e3/p.Cm;//-0.6e3/p.Cm;  // [pA/pF]
    
    // Cell structure
    double radius, length, pi;
    pi     = 3.14159265358979;    // [dimensionless]
    radius = 0.00005;             // [dm]
    length = 1.0 / ( 2 * pi * radius ) * ( p.Cm / ( 1e8 * p.Cm_surf ) - 2 * pi * pow( radius , 2 ) ); // [dm]
    
    p.Vcell = pi * pow( radius , 2 ) * length; // [L]
    p.Vsl   = 0.01 * p.Vcell;                  // [L]
    p.Vcyto = 0.46 * p.Vcell - p.Vsl;          // [L]
    p.VnSR  = 0.0116 * p.Vcell;                // [L]
    p.VjSR  = 0.0012 * p.Vcell;                // [L]
    
    // Concentrations (constant OR initial condition) ==================\\|
    p.Nao   = 140;                             // [mM]
    p.Ko    = 5.4;                             // [mM]
    p.Cao   = 2;                               // [mM]
    
    // Buffering
    p.Bmax_CaM 		= 0.045;   // [mM]
    p.Bmax_TnClow 	= 0.031;   // [mM]
    p.Bmax_TnChigh 	= 0.062;   // [mM]
    p.Bmax_Csqn 	= 10; 	   // [mM]
    p.kon_cam 		= 227.7;   // [mM^-1 ms^-1]
    p.kon_tncl 		= 88.8;    // [mM^-1 ms^-1]
    p.kon_tnchca	= 227.7;   // [mM^-1 ms^-1]
    p.kon_tnchmg	= 2.277;   // [mM^-1 ms^-1]
    p.kon_csqn 		= 0.534;   // [mM^-1 ms^-1]
    p.koff_cam 		= 0.542;   // [ms^-1]
    p.koff_tncl 	= 0.446;   // [ms^-1]
    p.koff_tnchca 	= 0.00751; // [ms^-1]
    p.koff_tnchmg 	= 0.751;   // [ms^-1]
    p.koff_csqn 	= 0.445;   // [ms^-1]
    p.Mgi 		= 2.5;     // [mM]
    
    // Current parameters
    p.gNaL 		= ( 1.5 * 0.17 ) * 2.5e-6 / p.Cm * 1e3; // [nS/pF]
    p.gNa 		= ( 2.2 ) * p.gNaL; 			// [nS/pF]
    p.gCaL		= ( 1 ) * 0.07; 			// [nS/pF]
    p.gCaD 		= 1.95 * p.gCaL; 			// [nS/pF]
    p.gCaT 		= 0.86 * 0.0068 / p.Cm * 1e3; 		// [nS/pF]
    p.gK1  		= ( 1 ) * 0.001525 / p.Cm * 1e3; 	// [nS/pF]
    p.gKr  		= ( 0.3 ) * 0.005 / p.Cm * 1e3; 	// [nS/pF]
    p.gto  		= ( 1.8 ) * 0.000491 / p.Cm * 1e3; 	// [nS/pF]
    p.gsus 		= ( 5 ) *0.0000665 / p.Cm * 1e3; 	// [nS/pF]
    p.gKs 		= ( 80 ) * 0.000518 / p.Cm * 1e3; 	// [nS/pF]
    p.gf 		= 0.228 * 25 / p.Cm * 0.8; 		// [nS/pF]
    p.gNab 		= 2 * 0.000058 / p.Cm * 1e3; 		// [nS/pF]
    p.gKb 		= 0.0000252 / p.Cm * 1e3; 		// [nS/pF]
    p.gCab 		= 0.5 * 0.0000132 / p.Cm * 1e3; 	// [nS/pF]
    p.gst 		= ( 0.2 ) * 0.017 / p.Cm * 1e3; 	// [nS/pF]
    p.gSK 		= 0.004; 				// [nS/pF]
    p.gKACh             = 0.0000001 * pow( p.Ko , 0.41 );               // [pA/(pF mM)]
    
    // IKr fraction of slow gates
    p.FKr = 0; // [-]
    
    // INaK pump
    p.INaK_bar		= 47.8 * 3;	// [pA]
    p.INaK_kK		= 0.621;	// [mM]
    p.INaK_kNa		= 5.64;		// [mM] 
    
    // INCX
    p.INCX_bar		= 7000;		// [pA/pF]
    p.INCX_ksat		= 0.1;		// [-]
    p.INCX_gamma	= 0.35;		// [-]
    p.INCX_kNao		= 87.5;		// [mM]
    p.INCX_kCao		= 1.38;		// [mM]
    p.INCX_alpha	= 2.5;		// [-]
    
    // SERCA pump
    p.ks 		= 250; 		// [ms^-1]
    p.J_SERCA_max 	= 0.04; 	// [mM/ms]
    p.hillSRCaP 	= 2; 		// [-]
    p.Kmf 		= 0.000246; 	// [mM]
    p.Kmr 		= 3.29; 	// [mM]
    
    // Release
    p.MaxSR 		= 15; 		// [-]
    p.MinSR 		= 1; 		// [-]
    p.HSR 		= 2.5; 		// [-]
    p.ec50SR 		= 0.45; 	// [-]
    p.koCa 		= 1.5; 		// [mM^-2 ms^-1]
    p.kiCa 		= 0.05; 	// [mM^-1 ms^-1]
    p.kom 		= 0.06; 	// [ms^-1]
    p.kim 		= 0.005; 	// [mM^-1 ms^-1]
    
    // Transfer between compartments
    p.J_jsr_nsr_tau	= 60; 		// [ms]
    p.J_i_sl_tau    	= 0.4; 		// [ms]
    
    // Distance between cells
    p.deltax = 65; // [um]
    p.ggap   = 40;   // [nS/pF]
}
//////////////////END SET PARAMETERS//////////////////////

void set_initial_conditions(State_variables &s, const char* filename, Parameters &p, Simulation &Sim)
{

	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "The file " << filename << " could not be opened" << std::endl;
		return;  
	}
	std::string line;
	int count = 0;
	
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string cell;
		while (std::getline(ss, cell, ','))
		{
			count++;
		}
	}
	
	double* data = new double[count];
	file.clear();
	file.seekg(0);
	
	int index = 0;
	while (std::getline(file,line))
	{
		std::stringstream ss(line);
		std::string cell;
		while (std::getline(ss,cell,','))
		{
			data[index++] = std::stod(cell);
		}
	}
	file.close();
	
	Sim.nbrecell = count / Sim.n_states;
	
	s.Vm 		= new double[Sim.nbrecell];
	s.Nai 		= new double[Sim.nbrecell];
	s.Ki 		= new double[Sim.nbrecell];
	s.Cai 		= new double[Sim.nbrecell];
	s.Cai_sl 	= new double[Sim.nbrecell];
	s.CanSR 	= new double[Sim.nbrecell];
	s.CajSR 	= new double[Sim.nbrecell];
	s.Nao 		= new double[Sim.nbrecell];
	s.Ko 		= new double[Sim.nbrecell];
	s.Cao 		= new double[Sim.nbrecell];
	s.CaM_i 	= new double[Sim.nbrecell];
	s.CaM_s 	= new double[Sim.nbrecell];
	s.Tn_CL 	= new double[Sim.nbrecell];
	s.Tn_CHc 	= new double[Sim.nbrecell];
	s.Tn_CHm 	= new double[Sim.nbrecell];
	s.csqn 		= new double[Sim.nbrecell];
	s.RyRr 		= new double[Sim.nbrecell];
	s.RyRo 		= new double[Sim.nbrecell];
	s.RyRi 		= new double[Sim.nbrecell];
	s.INa_va 	= new double[Sim.nbrecell];
	s.INa_vi_1 	= new double[Sim.nbrecell];
	s.INa_vi_2 	= new double[Sim.nbrecell];
	s.INa_vi 	= new double[Sim.nbrecell];
	s.INaL_va 	= new double[Sim.nbrecell];
	s.INaL_vi_1 	= new double[Sim.nbrecell];
	s.INaL_vi_2 	= new double[Sim.nbrecell];
	s.INaL_vi 	= new double[Sim.nbrecell];
	s.ICaL_va 	= new double[Sim.nbrecell];
	s.ICaL_vi 	= new double[Sim.nbrecell];
	s.ICaD_va 	= new double[Sim.nbrecell];
	s.ICaD_vi 	= new double[Sim.nbrecell];
	s.ICaT_va 	= new double[Sim.nbrecell];
	s.ICaT_vi 	= new double[Sim.nbrecell];
	s.IKr_va 	= new double[Sim.nbrecell];
	s.IKr_va_s 	= new double[Sim.nbrecell];
	s.IKr_vi 	= new double[Sim.nbrecell];
	s.Ito_vi 	= new double[Sim.nbrecell];
	s.Ito_va 	= new double[Sim.nbrecell];
	s.If_va 	= new double[Sim.nbrecell];
	s.Ist_va 	= new double[Sim.nbrecell];
	s.Ist_vi 	= new double[Sim.nbrecell];
	s.IKs_va 	= new double[Sim.nbrecell];
	s.ISK_va 	= new double[Sim.nbrecell];
	s.Vm_Phi 	= new double[Sim.nbrecell];
	s.IKur_Phi_va 	= new double[Sim.nbrecell];
	s.IKur_Phi_vi 	= new double[Sim.nbrecell];
	s.Shk_Phi_C0 	= new double[Sim.nbrecell];
	s.Shk_Phi_C1 	= new double[Sim.nbrecell];
	s.Shk_Phi_C2 	= new double[Sim.nbrecell];
	s.Shk_Phi_C3 	= new double[Sim.nbrecell];
	s.Shk_Phi_C4 	= new double[Sim.nbrecell];
	s.Shk_Phi_O 	= new double[Sim.nbrecell];
	s.Shk_Phi_I 	= new double[Sim.nbrecell];
	
	int Nc = Sim.nbrecell;
	int N  = Sim.n_states; 
	for (int i = 0; i < Nc; i++)
	{
		s.Vm[i] 	= data[i*N+0];
		s.INa_va[i] 	= data[i*N+1];
		s.INa_vi_1[i] 	= data[i*N+2];
		s.INa_vi_2[i] 	= data[i*N+3];
		s.INa_vi[i] 	= data[i*N+2];
		s.INaL_va[i] 	= data[i*N+4];
		s.INaL_vi_1[i] 	= data[i*N+5];
		s.INaL_vi_2[i] 	= data[i*N+6];
		s.INaL_vi[i] 	= data[i*N+5];
		s.ICaL_va[i] 	= data[i*N+8];
		s.ICaL_vi[i] 	= data[i*N+9];
		s.ICaD_va[i] 	= data[i*N+10];
		s.ICaD_vi[i] 	= data[i*N+11];
		s.ICaT_va[i] 	= data[i*N+12];
		s.ICaT_vi[i] 	= data[i*N+13];
		s.IKr_va[i]	= data[i*N+14];
		s.IKr_va_s[i]	= data[i*N+15];
		s.IKr_vi[i]	= data[i*N+16];
		s.Ito_vi[i]	= data[i*N+17];
		s.Ito_va[i]	= data[i*N+18];
		s.If_va[i]	= data[i*N+19];
		s.Ist_va[i]	= data[i*N+20];
		s.Ist_vi[i]	= data[i*N+21];
		s.IKs_va[i]	= data[i*N+22];
		s.ISK_va[i]	= data[i*N+23];
		s.RyRr[i]	= data[i*N+24];
		s.RyRo[i]	= data[i*N+25];
		s.RyRi[i]	= data[i*N+26];
		s.Nai[i]	= data[i*N+27];
		s.Ki[i]		= data[i*N+28];
		s.Cai[i]	= data[i*N+29];
		s.Cai_sl[i]	= data[i*N+30];
		s.CanSR[i]	= data[i*N+31];
		s.CajSR[i]	= data[i*N+32];
		s.Tn_CL[i]	= p.Bmax_TnClow  * data[i*N+33];
		s.Tn_CHc[i]	= p.Bmax_TnChigh * data[i*N+34];
		s.Tn_CHm[i]	= p.Bmax_TnChigh * data[i*N+35];
		s.CaM_i[i]	= p.Bmax_CaM     * data[i*N+36];
		s.CaM_s[i]	= p.Bmax_CaM     * data[i*N+37];
		s.csqn[i]	= p.Bmax_Csqn    * data[i*N+38];
		s.Vm_Phi[i]	= data[i*N+41];
		
		s.IKur_Phi_va[i]= 5.221596093580584e-1;
		s.IKur_Phi_vi[i]= 5.807741743166743e-1;
		s.Shk_Phi_C0[i]	= 0;
		s.Shk_Phi_C1[i]	= 0;
		s.Shk_Phi_C2[i]	= 0;
		s.Shk_Phi_C3[i]	= 0;
		s.Shk_Phi_C4[i]	= 0;
		s.Shk_Phi_O[i]	= 0;
		s.Shk_Phi_I[i]	= 0;
	}
};

void set_default_initial_conditions(State_variables &s, Parameters &p, Simulation &Sim)
{
	s.Vm 		= new double[Sim.nbrecell];
	s.Nai 		= new double[Sim.nbrecell];
	s.Ki 		= new double[Sim.nbrecell];
	s.Cai 		= new double[Sim.nbrecell];
	s.Cai_sl 	= new double[Sim.nbrecell];
	s.CanSR 	= new double[Sim.nbrecell];
	s.CajSR 	= new double[Sim.nbrecell];
	s.Nao 		= new double[Sim.nbrecell];
	s.Ko 		= new double[Sim.nbrecell];
	s.Cao 		= new double[Sim.nbrecell];
	s.CaM_i 	= new double[Sim.nbrecell];
	s.CaM_s 	= new double[Sim.nbrecell];
	s.Tn_CL 	= new double[Sim.nbrecell];
	s.Tn_CHc 	= new double[Sim.nbrecell];
	s.Tn_CHm 	= new double[Sim.nbrecell];
	s.csqn 		= new double[Sim.nbrecell];
	s.RyRr 		= new double[Sim.nbrecell];
	s.RyRo 		= new double[Sim.nbrecell];
	s.RyRi 		= new double[Sim.nbrecell];
	s.INa_va 	= new double[Sim.nbrecell];
	s.INa_vi_1 	= new double[Sim.nbrecell];
	s.INa_vi_2 	= new double[Sim.nbrecell];
	s.INa_vi 	= new double[Sim.nbrecell];
	s.INaL_va 	= new double[Sim.nbrecell];
	s.INaL_vi_1 	= new double[Sim.nbrecell];
	s.INaL_vi_2 	= new double[Sim.nbrecell];
	s.INaL_vi 	= new double[Sim.nbrecell];
	s.ICaL_va 	= new double[Sim.nbrecell];
	s.ICaL_vi 	= new double[Sim.nbrecell];
	s.ICaD_va 	= new double[Sim.nbrecell];
	s.ICaD_vi 	= new double[Sim.nbrecell];
	s.ICaT_va 	= new double[Sim.nbrecell];
	s.ICaT_vi 	= new double[Sim.nbrecell];
	s.IKr_va 	= new double[Sim.nbrecell];
	s.IKr_va_s 	= new double[Sim.nbrecell];
	s.IKr_vi 	= new double[Sim.nbrecell];
	s.Ito_vi 	= new double[Sim.nbrecell];
	s.Ito_va 	= new double[Sim.nbrecell];
	s.If_va 	= new double[Sim.nbrecell];
	s.Ist_va 	= new double[Sim.nbrecell];
	s.Ist_vi 	= new double[Sim.nbrecell];
	s.IKs_va 	= new double[Sim.nbrecell];
	s.ISK_va 	= new double[Sim.nbrecell];
	s.Vm_Phi 	= new double[Sim.nbrecell];
	s.IKur_Phi_va 	= new double[Sim.nbrecell];
	s.IKur_Phi_vi 	= new double[Sim.nbrecell];
	s.Shk_Phi_C0 	= new double[Sim.nbrecell];
	s.Shk_Phi_C1 	= new double[Sim.nbrecell];
	s.Shk_Phi_C2 	= new double[Sim.nbrecell];
	s.Shk_Phi_C3 	= new double[Sim.nbrecell];
	s.Shk_Phi_C4 	= new double[Sim.nbrecell];
	s.Shk_Phi_O 	= new double[Sim.nbrecell];
	s.Shk_Phi_I 	= new double[Sim.nbrecell];
	
	int Nc = Sim.nbrecell;
	int N  = Sim.n_states; 
	for (int i = 0; i < Nc; i++)
	{
		s.Vm[i] 	= -57.415813672267284;			//data[i*N+0];
		s.INa_va[i] 	= 0.016223950804206;			//data[i*N+1];
		s.INa_vi_1[i] 	= 0.128036249067985;			//data[i*N+2];
		s.INa_vi_2[i] 	= 0.128088190673968;			//data[i*N+3];
		s.INa_vi[i] 	= s.INa_vi_1[i];			//data[i*N+2];
		s.INaL_va[i] 	= 0.037811159760046;			//data[i*N+4];
		s.INaL_vi_1[i] 	= 0.616665289315549;			//data[i*N+5];
		s.INaL_vi_2[i] 	= 0.616811466129896;			//data[i*N+6];
		s.INaL_vi[i] 	= s.INaL_vi_1[i];			//data[i*N+5];
		s.ICaL_va[i] 	= 6.842332418939439e-6;			//data[i*N+8];
		s.ICaL_vi[i] 	= 0.906080059076503;			//data[i*N+9];
		s.ICaD_va[i] 	= 2.554993242778430e-4;			//data[i*N+10];
		s.ICaD_vi[i] 	= 0.803394439176479;			//data[i*N+11];
		s.ICaT_va[i] 	= 0.051900987767743;			//data[i*N+12];
		s.ICaT_vi[i] 	= 0.033402217298612;			//data[i*N+13];
		s.IKr_va[i]	= 0.004488039321316;			//data[i*N+14];
		s.IKr_va_s[i]	= 0.598289662518665;			//data[i*N+15];
		s.IKr_vi[i]	= 0.998560597913490;			//data[i*N+16];
		s.Ito_vi[i]	= 0.489586385933618;			//data[i*N+17];
		s.Ito_va[i]	= 0.029879291534843;			//data[i*N+18];
		s.If_va[i]	= 0.016548812921917;			//data[i*N+19];
		s.Ist_va[i]	= 0.142542169708870;			//data[i*N+20];
		s.Ist_vi[i]	= 0.053860077924092;			//data[i*N+21];
		s.IKs_va[i]	= 0.103559212488164;			//data[i*N+22];
		s.ISK_va[i]	= 0.915802431789431;			//data[i*N+23];
		s.RyRr[i]	= 0.997073471157958;			//data[i*N+24];
		s.RyRo[i]	= 3.563975414877186e-8;			//data[i*N+25];
		s.RyRi[i]	= 1.046029742331087e-10;		//data[i*N+26];
		s.Nai[i]	= 7.731677067572462;			//data[i*N+27];
		s.Ki[i]		= 1.587047891033031e+2;			//data[i*N+28];
		s.Cai[i]	= 1.554930932443314e-4;			//data[i*N+29];
		s.Cai_sl[i]	= 2.849740025330798e-5;			//data[i*N+30];
		s.CanSR[i]	= 2.094916158244747;			//data[i*N+31];
		s.CajSR[i]	= 2.042805150881959;			//data[i*N+32];
		s.Tn_CL[i]	= 0.030038527425053 * p.Bmax_TnClow;	//p.Bmax_TnClow  * data[i*N+33];
		s.Tn_CHc[i]	= 0.359012996113905 * p.Bmax_TnChigh;	//p.Bmax_TnChigh * data[i*N+34];
		s.Tn_CHm[i]	= 0.566271990595895 * p.Bmax_TnChigh;	//p.Bmax_TnChigh * data[i*N+35];
		s.CaM_i[i]	= 0.061332920922608 * p.Bmax_CaM;	//p.Bmax_CaM     * data[i*N+36];
		s.CaM_s[i]	= 0.011842974363814 * p.Bmax_CaM;	//p.Bmax_CaM     * data[i*N+37];
		s.csqn[i]	= 0.715429672905990 * p.Bmax_Csqn;	//p.Bmax_Csqn    * data[i*N+38];
		s.Vm_Phi[i]	= -50.663403052348180;			//data[i*N+41];
		
		s.IKur_Phi_va[i]= 5.221596093580584e-1;
		s.IKur_Phi_vi[i]= 5.807741743166743e-1;
		s.Shk_Phi_C0[i]	= 0;
		s.Shk_Phi_C1[i]	= 0;
		s.Shk_Phi_C2[i]	= 0;
		s.Shk_Phi_C3[i]	= 0;
		s.Shk_Phi_C4[i]	= 0;
		s.Shk_Phi_O[i]	= 0;
		s.Shk_Phi_I[i]	= 0;
	}
};

void set_default_initial_conditions_v2(State_variables &s, Parameters &p, Simulation &Sim)
{
	s.Vm 		= new double[Sim.nbrecell];
	s.Nai 		= new double[Sim.nbrecell];
	s.Ki 		= new double[Sim.nbrecell];
	s.Cai 		= new double[Sim.nbrecell];
	s.Cai_sl 	= new double[Sim.nbrecell];
	s.CanSR 	= new double[Sim.nbrecell];
	s.CajSR 	= new double[Sim.nbrecell];
	s.Nao 		= new double[Sim.nbrecell];
	s.Ko 		= new double[Sim.nbrecell];
	s.Cao 		= new double[Sim.nbrecell];
	s.CaM_i 	= new double[Sim.nbrecell];
	s.CaM_s 	= new double[Sim.nbrecell];
	s.Tn_CL 	= new double[Sim.nbrecell];
	s.Tn_CHc 	= new double[Sim.nbrecell];
	s.Tn_CHm 	= new double[Sim.nbrecell];
	s.csqn 		= new double[Sim.nbrecell];
	s.RyRr 		= new double[Sim.nbrecell];
	s.RyRo 		= new double[Sim.nbrecell];
	s.RyRi 		= new double[Sim.nbrecell];
	s.INa_va 	= new double[Sim.nbrecell];
	s.INa_vi_1 	= new double[Sim.nbrecell];
	s.INa_vi_2 	= new double[Sim.nbrecell];
	s.INa_vi 	= new double[Sim.nbrecell];
	s.INaL_va 	= new double[Sim.nbrecell];
	s.INaL_vi_1 	= new double[Sim.nbrecell];
	s.INaL_vi_2 	= new double[Sim.nbrecell];
	s.INaL_vi 	= new double[Sim.nbrecell];
	s.ICaL_va 	= new double[Sim.nbrecell];
	s.ICaL_vi 	= new double[Sim.nbrecell];
	s.ICaD_va 	= new double[Sim.nbrecell];
	s.ICaD_vi 	= new double[Sim.nbrecell];
	s.ICaT_va 	= new double[Sim.nbrecell];
	s.ICaT_vi 	= new double[Sim.nbrecell];
	s.IKr_va 	= new double[Sim.nbrecell];
	s.IKr_va_s 	= new double[Sim.nbrecell];
	s.IKr_vi 	= new double[Sim.nbrecell];
	s.Ito_vi 	= new double[Sim.nbrecell];
	s.Ito_va 	= new double[Sim.nbrecell];
	s.If_va 	= new double[Sim.nbrecell];
	s.Ist_va 	= new double[Sim.nbrecell];
	s.Ist_vi 	= new double[Sim.nbrecell];
	s.IKs_va 	= new double[Sim.nbrecell];
	s.ISK_va 	= new double[Sim.nbrecell];
	s.Vm_Phi 	= new double[Sim.nbrecell];
	s.IKur_Phi_va 	= new double[Sim.nbrecell];
	s.IKur_Phi_vi 	= new double[Sim.nbrecell];
	s.Shk_Phi_C0 	= new double[Sim.nbrecell];
	s.Shk_Phi_C1 	= new double[Sim.nbrecell];
	s.Shk_Phi_C2 	= new double[Sim.nbrecell];
	s.Shk_Phi_C3 	= new double[Sim.nbrecell];
	s.Shk_Phi_C4 	= new double[Sim.nbrecell];
	s.Shk_Phi_O 	= new double[Sim.nbrecell];
	s.Shk_Phi_I 	= new double[Sim.nbrecell];
	
	int Nc = Sim.nbrecell;
	int N  = Sim.n_states; 
	for (int i = 0; i < Nc; i++)
	{
		s.Vm[i] 	= -60.1;			//data[i*N+0];
		s.INa_va[i] 	= 0.135;			//data[i*N+1];
		s.INa_vi_1[i] 	= 0.03123;			//data[i*N+2];
		s.INa_vi_2[i] 	= 1;			//data[i*N+3];
		s.INa_vi[i] 	= s.INa_vi_1[i];			//data[i*N+2];
		s.INaL_va[i] 	= 0.135;			//data[i*N+4];
		s.INaL_vi_1[i] 	= 0.03123;			//data[i*N+5];
		s.INaL_vi_2[i] 	= 1;			//data[i*N+6];
		s.INaL_vi[i] 	= s.INaL_vi_1[i];			//data[i*N+5];
		s.ICaL_va[i] 	= 0.02248;			//data[i*N+8];
		s.ICaL_vi[i] 	= 0.43;			//data[i*N+9];
		s.ICaD_va[i] 	= 0.02248;			//data[i*N+10];
		s.ICaD_vi[i] 	= 0.531;			//data[i*N+11];
		s.ICaT_va[i] 	= 0.2217;			//data[i*N+12];
		s.ICaT_vi[i] 	= 0.06274;			//data[i*N+13];
		s.IKr_va[i]	= 0.002359413;			//data[i*N+14];
		s.IKr_va_s[i]	= 0.09102082;			//data[i*N+15];
		s.IKr_vi[i]	= 0.9977152;			//data[i*N+16];
		s.Ito_vi[i]	= 0.06609;			//data[i*N+17];
		s.Ito_va[i]	= 0.05733;			//data[i*N+18];
		s.If_va[i]	= 0.007645;			//data[i*N+19];
		s.Ist_va[i]	= 0.0015225;			//data[i*N+20];
		s.Ist_vi[i]	= 0.283;			//data[i*N+21];
		s.IKs_va[i]	= 0;			//data[i*N+22];
		s.ISK_va[i]	= 0.99979196;			//data[i*N+23];
		s.RyRr[i]	= 0.64484881;			//data[i*N+24];
		s.RyRo[i]	= 0.000012240116;			//data[i*N+25];
		s.RyRi[i]	= 0.0000067409369;		//data[i*N+26];
		s.Nai[i]	= 7;			//data[i*N+27];
		s.Ki[i]		= 159.43881;			//data[i*N+28];
		s.Cai[i]	= 0.0000326892;			//data[i*N+29];
		s.Cai_sl[i]	= 0.0000534741;			//data[i*N+30];
		s.CanSR[i]	= 4.5887879;			//data[i*N+31];
		s.CajSR[i]	= 3.431262;			//data[i*N+32];
		s.Tn_CL[i]	= 0.45367981 * p.Bmax_TnClow;	//p.Bmax_TnClow  * data[i*N+33];
		s.Tn_CHc[i]	= 0.93724623 * p.Bmax_TnChigh;	//p.Bmax_TnChigh * data[i*N+34];
		s.Tn_CHm[i]	= 0.05542706 * p.Bmax_TnChigh;	//p.Bmax_TnChigh * data[i*N+35];
		s.CaM_i[i]	= 0.6364781 * p.Bmax_CaM;	//p.Bmax_CaM     * data[i*N+36];
		s.CaM_s[i]	= 0.29785784 * p.Bmax_CaM;	//p.Bmax_CaM     * data[i*N+37];
		s.csqn[i]	= 0.84628533 * p.Bmax_Csqn;	//p.Bmax_Csqn    * data[i*N+38];
		s.Vm_Phi[i]	= -50.6634;			//data[i*N+41];
		
		s.IKur_Phi_va[i]= 5.221596093580584e-1;
		s.IKur_Phi_vi[i]= 5.807741743166743e-1;
		s.Shk_Phi_C0[i]	= 0;
		s.Shk_Phi_C1[i]	= 0;
		s.Shk_Phi_C2[i]	= 0;
		s.Shk_Phi_C3[i]	= 0;
		s.Shk_Phi_C4[i]	= 0;
		s.Shk_Phi_O[i]	= 0;
		s.Shk_Phi_I[i]	= 0;
	}
};


void allocate_variables(Model_variables &v, int n)
{
	v.ENa 			= new double[n];
	v.EK 			= new double[n];
	v.EKs_BM 		= new double[n];
	v.ECa 			= new double[n];
	v.ECa_sl 		= new double[n];
	
	v.Itot 			= new double[n];
	
	v.INa			= new double[n];
	v.INa_va_ss 		= new double[n];
	v.INa_va_tau		= new double[n];
	v.INa_vi_1_ss		= new double[n];
	v.INa_vi_2_ss		= new double[n];
	v.INa_vi_1_tau		= new double[n];
	v.INa_vi_2_tau		= new double[n];
	
	v.INaL_va_ss		= new double[n];
	v.INaL_va_tau		= new double[n];
	v.INaL_vi_ss		= new double[n];
	v.INaL_vi_tau		= new double[n];
	v.INaL_vi_2_tau		= new double[n];
	v.INaL			= new double[n];
	
	v.ICaL_va_tau		= new double[n];
	v.ICaL_va_ss		= new double[n];
	v.ICaL_vi_tau		= new double[n];
	v.ICaL_vi_ss		= new double[n];
	v.ICaL			= new double[n];
	
	v.ICaD_va_tau		= new double[n];
	v.ICaD_va_ss		= new double[n];
	v.ICaD_vi_tau		= new double[n];
	v.ICaD_vi_ss		= new double[n];
	v.ICaD			= new double[n];
	
	v.ICaT_va_tau		= new double[n];
	v.ICaT_va_ss		= new double[n];
	v.ICaT_vi_tau		= new double[n];
	v.ICaT_vi_ss		= new double[n];
	v.ICaT			= new double[n];
	
	v.IK1			= new double[n];
	
	v.IKr_va_tau		= new double[n];
	v.IKr_va_s_tau 		= new double[n];
	v.IKr_va_ss		= new double[n];
	v.IKr_vi_tau		= new double[n];
	v.IKr_vi_ss		= new double[n];
	v.IKr			= new double[n];
	
	v.Ito_va_tau		= new double[n];
	v.Ito_va_ss		= new double[n];
	v.Ito_vi_tau		= new double[n];
	v.Ito_vi_ss		= new double[n];
	v.Ito			= new double[n];
	v.Isus			= new double[n];
	
	v.IKs_va_al		= new double[n];
	v.IKs_va_bet		= new double[n];
	v.IKs_va_ss		= new double[n];
	v.IKs_va_tau		= new double[n];
	v.IKs			= new double[n];
	
	v.If_va_ss		= new double[n];
	v.If_va_tau		= new double[n];
	v.If_Na			= new double[n];
	v.If_K			= new double[n];
	v.If			= new double[n];
	
	v.INab			= new double[n];
	v.IKb			= new double[n];
	v.ICab			= new double[n];
	
	v.INaK			= new double[n];
	
	v.INCX			= new double[n];
	
	v.Ist_va_ss		= new double[n];
	v.Ist_va_tau		= new double[n];
	v.Ist_vi_ss		= new double[n];
	v.Ist_vi_tau		= new double[n];
	v.Ist			= new double[n];
	
	v.ISK_va_ss 		= new double[n];
	v.ISK_va_tau		= new double[n];
	v.ISK			= new double[n];
	
	v.IKACh			= new double[n];
	
	v.J_jsr_nsr		= new double[n];
	v.J_i_sl		= new double[n];
	v.dTn_CL		= new double[n];
	v.dTn_CHc		= new double[n];
	v.dTn_CHm		= new double[n];
	v.dCaM_i		= new double[n];
	v.dCaM_s		= new double[n];
	v.dcsqn			= new double[n];
	
	v.kCaSR			= new double[n];
	v.koSRCa		= new double[n];
	v.kiSRCa		= new double[n];
	v.RI			= new double[n];
	v.J_rel			= new double[n];
	
	v.J_SERCA		= new double[n];
	
	v.Istim			= new double[n];
	v.Istim_Phi		= new double[n];
	
	v.Itot_Phi		= new double[n];
	
	v.IGap_AV1		= new double[n];
	v.IGap_Phi		= new double[n];
	
	v.Ib_Phi		= new double[n];
	
	v.IK1_Phi		= new double[n];
	
	v.dShk_C0_Phi		= new double[n];
	v.dShk_C1_Phi		= new double[n];
	v.dShk_C2_Phi		= new double[n];
	v.dShk_C3_Phi		= new double[n];
	v.dShk_C4_Phi		= new double[n];
	v.dShk_O_Phi		= new double[n];
	v.dShk_I_Phi		= new double[n];
	v.Ishk_Phi		= new double[n];
	
	v.IKur_Phi_va_ss	= new double[n];
	v.IKur_Phi_va_tau	= new double[n];
	v.IKur_Phi_vi_ss	= new double[n];
	v.IKur_Phi_vi_tau	= new double[n];
	v.IKur_Phi		= new double[n];
	
	v.IGap_AV		= new double[n];
	
	
};

/////////////////////// Reversal potentials //////////////////////////////////////////
void compute_reversal_potentials(Parameters p, Model_variables &var, State_variables s, int n)
{
	for (int i = 0; i < n; i++)
	{
    		var.ENa[i]            =       ((p.R * p.T)/p.F)*log(p.Nao/s.Nai[i]);
    		var.EK[i]             =       ((p.R * p.T)/p.F)*log(p.Ko/s.Ki[i]);
    		var.EKs_BM[i]         =       ((p.R * p.T)/p.F)*log((p.Ko + 0.1    *p.Nao)/(s.Ki[i] + 0.1    *s.Nai[i]));
    		var.ECa[i]            = 0.5*  ((p.R * p.T)/p.F)*log(p.Cao/s.Cai[i]);
    		var.ECa_sl[i]         = 0.5*  ((p.R * p.T)/p.F)*log(p.Cao/s.Cai_sl[i]);
    	}
};
/////////////////////////////////////////////////////////////////////////////////////////

////////////////////// Rush Larsen //////////////////////////////////////////////////////
double rush_larsen(double y, double ss, double tau, double dt)
{
    double gate;
    gate = ss - (ss-y)*exp(-dt/tau);
    return gate;
}
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// INa
void compute_INa_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s, int n )
{    
	double dt = p.dt;
	for (int i=0; i<n; i++)
	{
	    //=======INa=======//
	    double Vm_ac   = s.Vm[i];
	    double Vm_inac = s.Vm[i];
	    
	    // Voltage activation
	    var.INa_va_ss[i] = 1.0 / ( 1.0 + exp ( - ( Vm_ac + 41 ) / 4 ) );
	    var.INa_va_tau[i] = p.Q10 * ( 0.04 + ( 0.6247 / ( 0.832 * exp( -0.335 * ( Vm_ac + 56.7 ) ) + 0.627 * exp( 0.082 * ( Vm_ac + 65.01 ) ) ) ) );
	    
	    // Voltage inactivation
	    var.INa_vi_1_ss[i] = 1.0 / ( 1.0 + exp( ( Vm_inac + 65.1 ) / 4 ) );
	    var.INa_vi_2_ss[i] = var.INa_vi_1_ss[i];
	    var.INa_vi_1_tau[i] = p.Q10 * 0.113 / ( 1.0 / ( 13475.066 * exp( ( Vm_inac - 59.398 ) / 15.645 ) ) + 1.0 / ( 1.113 + 0.044 * exp( - ( Vm_inac - 86.768 ) / 8.059 ) ) );
	    var.INa_vi_2_tau[i] = p.Q10 * 0.125 / ( 1.0 / ( 140557.232 * exp( ( Vm_inac - 59.455 ) / 12 ) ) + 1.0 / ( 2.471 + 0.767 * exp( - ( Vm_inac - 68.931 ) / 18.237 ) ) );
	    
	    // Update gates
	    s.INa_va[i]   = rush_larsen( s.INa_va[i]   , var.INa_va_ss[i] , var.INa_va_tau[i]   , dt );
	    s.INa_vi_1[i] = rush_larsen( s.INa_vi_1[i] , var.INa_vi_1_ss[i] , var.INa_vi_1_tau[i] , dt );
	    s.INa_vi_2[i] = rush_larsen( s.INa_vi_2[i] , var.INa_vi_2_ss[i] , var.INa_vi_2_tau[i] , dt ); 
	    
	    double FNa = 8.69e-2 + ( 9.52e-2 * exp( - 6.3e-2 * ( Vm_inac + 34.4 ) ) ) / ( 1.0 + 1.66 * exp( - 0.225 * ( Vm_inac + 63.7 ) ) );
	    
	    s.INa_vi[i] = ( 1 - FNa ) * s.INa_vi_1[i] + FNa * s.INa_vi_2[i];
	    
	    // Compute INa
	    
	    var.INa[i] = p.gNa * pow( s.INa_va[i] , 3 ) * s.INa_vi[i] * p.Nao * p.F * p.FoRT * ( exp( ( s.Vm[i] - var.ENa[i] ) * p.FoRT ) - 1.0 ) / ( exp( s.Vm[i] * p.FoRT ) - 1.0 ) * s.Vm[i];   
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// INaL
void compute_INaL_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	double dt = p.dt;
	for (int i=0; i<n; i++)
	{
	    //=======INaL=======//
	    double Vm_ac   = s.Vm[i];
	    double Vm_inac = s.Vm[i];
	    
	    // Voltage activation
	    var.INaL_va_ss[i] = 1.0 / ( 1.0 + exp( - ( Vm_ac + 38 ) / 6 ) );
	    var.INaL_va_tau[i] = p.Q10 * ( 0.04 + ( 0.6247 / ( 0.832 * exp( -0.335 * ( Vm_ac + 56.7 ) ) + 0.627 * exp( 0.082 * ( Vm_ac + 65.01 ) ) ) ) );
	    
	    // Voltage inactivation
	    var.INaL_vi_ss[i] = 1.0 / ( 1.0 + exp( ( Vm_inac + 56 ) / 3 ) );
	    var.INaL_vi_tau[i] = p.Q10 * 0.113 / ( 1.0 / ( 13475.066 * exp( ( Vm_inac - 59.398 ) / 15.645 ) ) + 1.0 / ( 1.113 + 0.044 * exp( - ( Vm_inac - 86.768 ) / 8.059 ) ) );
	    var.INaL_vi_2_tau[i] = p.Q10 * 0.125 / ( 1.0 / ( 140557.232 * exp( ( Vm_inac - 59.455 ) / 12 ) ) + 1.0 / ( 2.471 + 0.767 * exp( - ( Vm_inac - 68.931 ) / 18.237 ) ) );
	    
	    // Update gates
	    s.INaL_va[i]   = rush_larsen( s.INaL_va[i]   , var.INaL_va_ss[i] , var.INaL_va_tau[i]   , dt );
	    s.INaL_vi_1[i] = rush_larsen( s.INaL_vi_1[i] , var.INaL_vi_ss[i] , var.INaL_vi_tau[i]   , dt );
	    s.INaL_vi_2[i] = rush_larsen( s.INaL_vi_2[i] , var.INaL_vi_ss[i] , var.INaL_vi_2_tau[i] , dt ); 
	    
	    double FNas = 8.69e-2 + ( 9.52e-2 * exp( - 6.3e-2 * ( Vm_inac + 34.4 ) ) ) / ( 1.0 + 1.66 * exp( - 0.225 * ( Vm_inac + 63.7 ) ) );
	    
	    s.INaL_vi[i] = ( 1 - FNas ) * s.INaL_vi_1[i] + FNas * s.INaL_vi_2[i];
	    
	    // Compute INaL
	    var.INaL[i] = p.gNaL * pow( s.INaL_va[i] , 3 ) * s.INaL_vi[i] * p.Nao * p.F * p.FoRT * ( exp( ( s.Vm[i] - var.ENa[i] ) * p.FoRT ) - 1.0 ) / ( exp( s.Vm[i] * p.FoRT ) - 1.0 ) * s.Vm[i];
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// ICaL
void compute_ICaL_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n,double f_Cav )
{
	double dt = p.dt;
	for (int i = 0; i<n; i++)
	{
	    double Vm_ac_ss    = s.Vm[i];
	    double Vm_inac_ss  = s.Vm[i];
	    double Vm_ac_tau   = s.Vm[i];
	    double Vm_inac_tau = s.Vm[i];
	    
	    if (Vm_ac_tau == -35.000000) Vm_ac_tau = -35 + 1e-10;
	    if (Vm_ac_tau == 0.000000) Vm_ac_tau = 0 + 1e-10;
	    if (Vm_ac_tau == 5.000000) Vm_ac_tau = 5 + 1e-10;
	    if (Vm_inac_tau == -68.000000) Vm_inac_tau = -68 + 1e-10;
	    
	    // Voltage activation
	    double alpha_ac = - 0.01419 * ( Vm_ac_tau + 35 ) / ( exp( - ( Vm_ac_tau + 35 ) / 2.5 ) - 1.0 ) - 0.04245 * ( Vm_ac_tau ) / ( exp( - 0.208 * Vm_ac_tau ) - 1.0 );
	    double beta_ac = 0.00571 * ( Vm_ac_tau - 5 ) / ( exp( 0.4 * ( Vm_ac_tau - 5 ) ) - 1.0 );
	    
	    var.ICaL_va_tau[i] = 1. / ( alpha_ac + beta_ac );
	    var.ICaL_va_ss[i] = 1.0 / ( 1.0 + exp( - ( Vm_ac_ss + 10 ) / 4 ) );
	    
	    // Voltage inactivation
	    double alpha_inac = 0.00312 * ( Vm_inac_tau + 68 ) / ( exp( ( Vm_inac_tau + 68 ) / 4 ) - 1.0 );
	    double beta_inac  = 0.025 / ( 1.0 + exp( - ( Vm_inac_tau + 68 ) / 4 ) );
	    
	    var.ICaL_vi_tau[i] = 1. / ( alpha_inac + beta_inac );
	    var.ICaL_vi_ss[i] = 1.0 / ( 1.0 + exp( ( Vm_inac_ss + 36 ) / 4.6 ) );
	    
	    // Update gates
	    s.ICaL_va[i] = rush_larsen( s.ICaL_va[i] , var.ICaL_va_ss[i] , var.ICaL_va_tau[i] , dt );
	    s.ICaL_vi[i] = rush_larsen( s.ICaL_vi[i] , var.ICaL_vi_ss[i] , var.ICaL_vi_tau[i] , dt );
	    
	    // Compute ICaL
	    var.ICaL[i] = f_Cav *p.gCaL * ( s.ICaL_va[i] * s.ICaL_vi[i] + 0.006 / ( 1.0 + exp( - ( s.Vm[i] + 14.1 ) / 6 ) ) ) * ( s.Vm[i] - var.ECa_sl[i] );
	}

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// ICaD
void compute_ICaD_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n, double f_Cav )
{
	double dt = p.dt;
	for (int i=0;i<n;i++)
	{
	    double Vm_ac_ss    = s.Vm[i];
	    double Vm_inac_ss  = s.Vm[i];
	    double Vm_ac_tau   = s.Vm[i];
	    double Vm_inac_tau = s.Vm[i];
	    
	    if (Vm_ac_tau == -35.000000) Vm_ac_tau = -35 + 1e-10;
	    if (Vm_ac_tau == 0.000000) Vm_ac_tau = 0 + 1e-10;
	    if (Vm_ac_tau == 5.000000) Vm_ac_tau = 5 + 1e-10;
	    if (Vm_inac_tau == -68.000000) Vm_inac_tau = -68 + 1e-10;
	    
	    // Voltage activation
	    double alpha_ac = - 0.01419 * ( Vm_ac_tau + 35 ) / ( exp( - ( Vm_ac_tau + 35 ) / 2.5 ) - 1.0 ) - 0.04245 * ( Vm_ac_tau ) / ( exp( - 0.208 * Vm_ac_tau ) - 1.0 );
	    double beta_ac  = 0.00571 * ( Vm_ac_tau - 5 ) / ( exp( 0.4 * ( Vm_ac_tau - 5 ) ) - 1.0 );
	    
	    var.ICaD_va_tau[i] = 1. / ( alpha_ac + beta_ac );
	    var.ICaD_va_ss[i]  = 1.0 / ( 1.0 + exp( - ( Vm_ac_ss + 22 ) / 4.3 ) );
	    
	    // Voltage inactivation
	    double alpha_inac = 0.00312 * ( Vm_inac_tau + 68 ) / ( exp( ( Vm_inac_tau + 68 ) / 4 ) - 1.0 );
	    double beta_inac  = 0.025 / ( 1.0 + exp( - ( Vm_inac_tau + 68 ) / 4 ) );
	    
	    var.ICaD_vi_tau[i]   = 1. / ( alpha_inac + beta_inac );
	    var.ICaD_vi_ss[i]    = 1.0 / ( 1.0 + exp( ( Vm_inac_ss + 48 ) / 5.4 ) );
	    
	    // Update gates
	    s.ICaD_va[i] = rush_larsen( s.ICaD_va[i] , var.ICaD_va_ss[i] , var.ICaD_va_tau[i] , dt );
	    s.ICaD_vi[i] = rush_larsen( s.ICaD_vi[i] , var.ICaD_vi_ss[i] , var.ICaD_vi_tau[i] , dt );
	    
	    // Compute ICaD
	    var.ICaD[i] = f_Cav * p.gCaD * ( s.ICaD_va[i] * s.ICaD_vi[i] + 0.006 / ( 1.0 + exp( - ( s.Vm[i] + 14.1 ) / 6 ) ) ) * ( s.Vm[i] - var.ECa_sl[i] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// ICaT
void compute_ICaT_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	double dt = p.dt;
	for (int i = 0; i < n; i++)
	{
	    double Vm_ac_ss    = s.Vm[i];
	    double Vm_inac_ss  = s.Vm[i];
	    double Vm_ac_tau   = s.Vm[i];
	    double Vm_inac_tau = s.Vm[i];
	    
	    // Voltage activation
	    double alpha_ac = 1.068 * exp(   ( Vm_ac_tau + 26.3 ) / 30 );
	    double beta_ac  = 1.068 * exp( - ( Vm_ac_tau + 26.3 ) / 30 );
	    
	    var.ICaT_va_tau[i] = 1. / ( alpha_ac + beta_ac );
	    var.ICaT_va_ss[i]  = 1.0 / ( 1.0 + exp( - ( Vm_ac_ss + 40 ) / 6 ) );
	    
	    // Voltage inactivation
	    double alpha_inac = 0.0153 * exp( - ( Vm_inac_tau + 71.7 ) / 83.3  );
	    double beta_inac  = 0.015  * exp(   ( Vm_inac_tau + 71.7 ) / 15.38 );
	    
	    var.ICaT_vi_tau[i]   = 1. / ( alpha_inac + beta_inac );
	    var.ICaT_vi_ss[i]    = 1.0 / ( 1.0 + exp( ( Vm_inac_ss + 71 ) / 3.4 ) );
	    
	    // Update gates
	    s.ICaT_va[i] = rush_larsen( s.ICaT_va[i] , var.ICaT_va_ss[i] , var.ICaT_va_tau[i] , dt );
	    s.ICaT_vi[i] = rush_larsen( s.ICaT_vi[i] , var.ICaT_vi_ss[i] , var.ICaT_vi_tau[i] , dt );
	    
	    // Compute ICaT
	    var.ICaT[i] = p.gCaT * s.ICaT_va[i] * s.ICaT_vi[i] * ( s.Vm[i] - var.ECa_sl[i] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// IK1
void compute_IK1_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	for( int i = 0; i < n; i++)
	{
    		var.IK1[i] = p.gK1 * ( s.Vm[i] - var.EK[i] ) / ( 1.0 + exp( 0.07 * ( s.Vm[i] + 80 ) ) );
    	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// IKr
void compute_IKr_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n ,double f_Kr)
{
	double dt = p.dt;
	for (int i = 0; i < n; i++)
	{
	    double Vm_ac_ss    = s.Vm[i];
	    double Vm_inac_ss  = s.Vm[i];
	    double Vm_ac_tau   = s.Vm[i];
	    
	    // Voltage activation
	    var.IKr_va_ss[i]    = 1.0 / ( 1.0 + exp( - ( Vm_ac_ss + 23 ) / 6.5 ) );
	    var.IKr_va_tau[i]   = 5.0 + ( 0.84655 / 2.6 ) / ( 0.0372 * exp( ( Vm_ac_tau - 15 ) / 20 ) + 0.00096 * exp( - ( Vm_ac_tau + 40 ) / 5 ) );
	    var.IKr_va_s_tau[i] = 0.84655 / ( 0.0042 * exp( Vm_ac_tau / 17 ) + 0.00015 * exp( - Vm_ac_tau / 21.6 ) ); 
	    
	    // Voltage inactivation
	    var.IKr_vi_ss[i] = 1.0 / ( 1.0 + exp( ( Vm_inac_ss + 15 ) / 6.5 ) );
	    var.IKr_vi_tau[i] = 2.0;
	    
	    // Update gates
	    s.IKr_va[i]   = rush_larsen( s.IKr_va[i]   , var.IKr_va_ss[i] , var.IKr_va_tau[i]   , dt ); 
	    s.IKr_va_s[i] = rush_larsen( s.IKr_va_s[i] , var.IKr_va_ss[i] , var.IKr_va_s_tau[i] , dt );
	    s.IKr_vi[i]   = rush_larsen( s.IKr_vi[i]   , var.IKr_vi_ss[i] , var.IKr_vi_tau[i]   , dt );
	    
	    // Compute IKr
	    var.IKr[i] = f_Kr * p.gKr * ( ( 1 - p.FKr ) * s.IKr_va[i] + p.FKr * s.IKr_va_s[i] ) * s.IKr_vi[i] * ( s.Vm[i] - var.EK[i] );
    	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// Ito & Isus
void compute_Ito_Isus_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	double dt = p.dt;
	for (int i = 0; i<n; i++)
	{
	    double Vm_ac_ss    = s.Vm[i];
	    double Vm_inac_ss  = s.Vm[i];
	    double Vm_ac_tau   = s.Vm[i];
	    double Vm_inac_tau = s.Vm[i];
	    
	    // Voltage inactivation
	    var.Ito_vi_ss[i]  = 1.0 / ( 1.0 + exp( ( Vm_inac_ss + 59.37 ) / 13.1 ) );
	    var.Ito_vi_tau[i] = 10.1 + 65.17 / ( 0.57 * exp( - 0.08 * ( Vm_inac_tau + 49 ) ) + 0.000024 * exp( 0.1 * ( Vm_inac_tau + 50.93 ) ) );
	    
	    // Voltage activation
	    var.Ito_va_ss[i]  = 1.0 / ( 1.0 + exp( - ( Vm_ac_ss - 10.93 ) / 19.7 ) );
	    var.Ito_va_tau[i] = 2.98 + 15.59 / ( 1.037 * exp( 0.09 * ( Vm_ac_tau + 30.61 ) ) + 0.369 * exp( - 0.12 * ( Vm_ac_tau + 23.84 ) ) );
	    
	    // Update gates
	    s.Ito_va[i] = rush_larsen( s.Ito_va[i] , var.Ito_va_ss[i] , var.Ito_va_tau[i] , dt );
	    s.Ito_vi[i] = rush_larsen( s.Ito_vi[i] , var.Ito_vi_ss[i] , var.Ito_vi_tau[i] , dt );
	    
	    var.Ito[i]  = p.gto  * s.Ito_vi[i] * s.Ito_va[i] * ( s.Vm[i] - var.EK[i] );
	    var.Isus[i] = p.gsus * s.Ito_va[i] * ( s.Vm[i] - var.EK[i] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// IKs
void compute_IKs_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n)
{
	double dt = p.dt;
	for (int i = 0; i < n; i++)
	{
	    double Vm_ac  = s.Vm[i];
	    
	    // Voltage activation
	    var.IKs_va_al[i]  = 0.014 / ( 1.0 + exp( - ( Vm_ac - 40 ) / 9 ) );
	    var.IKs_va_bet[i] = 0.001 * exp( - Vm_ac / 45 );
	    var.IKs_va_ss[i]  = var.IKs_va_al[i] / ( var.IKs_va_al[i] + var.IKs_va_bet[i] );
	    var.IKs_va_tau[i] = 1.0 / ( var.IKs_va_al[i] + var.IKs_va_bet[i] ); 
	    
	    // Update gate
	    s.IKs_va[i] = rush_larsen( s.IKs_va[i] , var.IKs_va_ss[i] , var.IKs_va_tau[i] , dt );
	    
	    // Compute IKs
	    var.IKs[i] = p.gKs * pow( s.IKs_va[i] , 2 ) * ( s.Vm[i] - var.EKs_BM[i] );
	 }

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// If
void compute_If_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	double dt = p.dt;
	for (int i = 0; i < n; i++)
	{
	    double Vm_ac_ss  = s.Vm[i];
	    double Vm_ac_tau = s.Vm[i];
	    
	    // Voltage activation
	    var.If_va_ss[i]  = 1.0 / ( 1.0 + exp( ( Vm_ac_ss + 97 ) / 20 ) );
	    var.If_va_tau[i] = 1.505 / ( exp( -0.0119 * ( Vm_ac_tau + 590.3 + 14 ) ) + exp( ( Vm_ac_tau - 55 + 14 ) / 10 ) );
	    
	    // Update gates
	    s.If_va[i] = rush_larsen( s.If_va[i] , var.If_va_ss[i] , var.If_va_tau[i] , dt );
	    
	    // Compute If
	    var.If_Na[i] = p.gf * 0.3833 * s.If_va[i] * ( s.Vm[i] - var.EK[i]  ); 
	    var.If_K[i]  = p.gf * 0.3833 * s.If_va[i] * ( s.Vm[i] - var.ENa[i] ); 
	    var.If[i]    = var.If_Na[i] + var.If_K[i];  
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// INab
void compute_INab_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	for (int i = 0; i < n; i++)
	{
    		var.INab[i] = p.gNab * ( s.Vm[i] - var.ENa[i] );
    	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// IKb
void compute_IKb_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	for (int i = 0; i < n; i++)
	{
    		var.IKb[i] = p.gKb * ( s.Vm[i] - var.EK[i] );
    	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// ICab
void compute_ICab_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	for (int i = 0; i < n; i++)
	{
    		var.ICab[i] = p.gCab * ( s.Vm[i] - var.ECa_sl[i] );
    	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// INaK
void compute_INaK_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	for (int i = 0; i < n; i++)
	{
    		var.INaK[i] = p.INaK_bar / p.Cm * pow( s.Nai[i] / ( p.INaK_kNa + s.Nai[i] ) , 3 ) * pow( p.Ko / ( p.INaK_kK + p.Ko ) , 2 ) * 1.6 / ( 1.5 + exp( - ( s.Vm[i] + 60 ) / 40 ) );
    	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// INCX
void compute_INCX_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	for (int i = 0; i < n; i++)
	{
    		double numerator = exp( p.INCX_gamma * s.Vm[i] * p.FoRT ) * pow( s.Nai[i] , 3 ) * p.Cao - exp( ( p.INCX_gamma - 1 ) * s.Vm[i] * p.FoRT ) * pow( p.Nao , 3 ) * s.Cai_sl[i] * p.INCX_alpha;
    
    		double denominator = ( pow( p.INCX_kNao , 3 ) + pow( p.Nao , 3 ) ) * ( p.INCX_kCao + p.Cao ) * ( 1.0 + p.INCX_ksat * exp( ( p.INCX_gamma - 1 ) * s.Vm[i] * p.FoRT ) );
    
    		var.INCX[i] = p.INCX_bar * numerator / denominator;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// Ist
void compute_Ist_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	double dt = p.dt;
	for (int i = 0; i < n; i++)
	{
	    double Vm_ac   = s.Vm[i];
	    double Vm_inac = s.Vm[i];
	    
	    // Voltage activation
	    double alpha_ac = 1.0 / ( 0.15 * exp( - Vm_ac / 11 ) + 0.2 * exp( - Vm_ac / 700 ) );
	    double beta_ac  = 1.0 / ( 16   * exp(   Vm_ac / 8  ) + 15  * exp(   Vm_ac / 50  ) );
	    var.Ist_va_ss[i]   = alpha_ac             / ( alpha_ac + beta_ac );
	    var.Ist_va_tau[i]  = 1. / ( alpha_ac + beta_ac );
	    
	    // Voltage inactivation
	    double alpha_inac = 1.0 / ( 3100 * exp( - Vm_inac / 13 ) + 700 * exp( - Vm_inac / 70  ) );
	    double beta_inac  = 1.0 / ( 95   * exp( - Vm_inac / 10 ) + 50  * exp(   Vm_inac / 700 ) ) + 2.29e-4 / ( 1.0 + exp( - Vm_inac / 5 ) );
	    var.Ist_vi_ss[i]     = alpha_inac           / ( alpha_inac + beta_inac );
	    var.Ist_vi_tau[i]    = 1. / ( alpha_inac + beta_inac );
	    
	    // Update gates
	    s.Ist_va[i] = rush_larsen( s.Ist_va[i] , var.Ist_va_ss[i] , var.Ist_va_tau[i] , dt );
	    s.Ist_vi[i] = rush_larsen( s.Ist_vi[i] , var.Ist_vi_ss[i] , var.Ist_vi_tau[i] , dt );
	    
	    // Compute Ist
	    var.Ist[i] = p.gst * s.Ist_va[i] * s.Ist_vi[i] * ( s.Vm[i] - 10 );
	}

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// ISK
void compute_ISK_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	double dt = p.dt;
	for (int i = 0; i < n; i++)
	{
	    double betaK = 100; 			// [ms^-1]
	    double nSK   = 1.7; 			// [-]
	    double Cac   = 7e-6; 			// [mM]
	    double Car   = pow( s.Cai_sl[i] / Cac , nSK ); // [-]
	    
	    // Voltage activation
	    var.ISK_va_ss[i]  = Car / ( 1.0 + Car );
	    var.ISK_va_tau[i] = 1e-3 / ( betaK * ( 1.0 + Car ) );
	    
	    // Update gates
	    s.ISK_va[i] = rush_larsen( s.ISK_va[i] , var.ISK_va_ss[i] , var.ISK_va_tau[i] , dt );
	    
	    // Compute ISK
	    var.ISK[i] = p.gSK * pow( s.ISK_va[i] , 2 ) * ( s.Vm[i] - var.EK[i] ); 
	}

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// IKACh
void compute_IKACh_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n , double f_KAch)
{
	for (int i = 0; i < n; i++)
	{
    		var.IKACh[i] = f_KAch * p.gKACh * ( s.Ki[i] - p.Ko * exp( - s.Vm[i] * p.FoRT ) );
    	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void compute_Jrel_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	double dt = p.dt;
	for (int i = 0; i < n; i++)
	{
	    var.kCaSR[i]  = p.MaxSR - ( p.MaxSR - p.MinSR ) / ( 1.0 + pow( p.ec50SR / s.CajSR[i] , p.HSR ) );
	    var.koSRCa[i] = p.koCa / var.kCaSR[i];
	    var.kiSRCa[i] = p.kiCa * var.kCaSR[i];
	    var.RI[i]     = 1 - s.RyRr[i] - s.RyRo[i] - s.RyRi[i];
	    
	    
	    double dRyRr = p.kim * var.RI[i] - var.kiSRCa[i] * s.Cai_sl[i] * s.RyRr[i] - ( var.koSRCa[i] * pow( s.Cai_sl[i] , 2 ) * s.RyRr[i] - p.kom * s.RyRo[i] );
	    double dRyRo = var.koSRCa[i] * pow( s.Cai_sl[i] , 2 ) * s.RyRr[i] - p.kom * s.RyRo[i] - ( var.kiSRCa[i] * s.Cai_sl[i] * s.RyRo[i] - p.kim * s.RyRi[i] );
	    double dRyRi = var.kiSRCa[i] * s.Cai_sl[i] * s.RyRo[i] - p.kim * s.RyRi[i] - ( p.kom * s.RyRi[i] - var.koSRCa[i] * pow( s.Cai_sl[i] , 2 ) * var.RI[i] );
	    
	    s.RyRr[i] += dt * dRyRr;
	    s.RyRo[i] += dt * dRyRo;
	    s.RyRi[i] += dt * dRyRi;
	    
	    // Compute Jrel
	    var.J_rel[i] = p.ks * s.RyRo[i] * ( s.CajSR[i] - s.Cai_sl[i] );
	}
}

void compute_Jserca_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	for (int i = 0; i < n; i++)
	{
	    double numerator = pow( s.Cai[i] / ( p.Kmf ) , p.hillSRCaP ) - pow( s.CanSR[i] / ( p.Kmr ) , p.hillSRCaP );
	    double denominator = 1 + pow( s.Cai[i] / ( p.Kmf ) , p.hillSRCaP ) + pow( s.CanSR[i] / ( p.Kmr ) , p.hillSRCaP );
	    var.J_SERCA[i] = p.J_SERCA_max * numerator / denominator;
	}
}

// Homeostasis
void compute_homeostasis_mAVNM_BM( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	double dt = p.dt;
	for (int i = 0; i < n; i++)
	{
	    // Compute Jrel
	    compute_Jrel_mAVNM_BM(   p , var , s , n );
	    
	    // Compute JSERCA
	    compute_Jserca_mAVNM_BM( p , var , s , n );
	    
	    // Compute transfer between compartments
	    var.J_jsr_nsr[i] = ( s.CanSR[i]  - s.CajSR[i] ) / p.J_jsr_nsr_tau;
	    var.J_i_sl[i]    = ( s.Cai_sl[i] - s.Cai[i]   ) / p.J_i_sl_tau;
	    
	    // Compute buffers
	    var.dTn_CL[i]  = p.kon_tncl   * s.Cai[i]    * ( p.Bmax_TnClow  - s.Tn_CL[i]             ) - p.koff_tncl   * s.Tn_CL[i];
	    var.dTn_CHc[i] = p.kon_tnchca * s.Cai[i]    * ( p.Bmax_TnChigh - s.Tn_CHc[i] - s.Tn_CHm[i] ) - p.koff_tnchca * s.Tn_CHc[i];
	    var.dTn_CHm[i] = p.kon_tnchmg * p.Mgi    * ( p.Bmax_TnChigh - s.Tn_CHc[i] - s.Tn_CHm[i] ) - p.koff_tnchmg * s.Tn_CHm[i];
	    var.dCaM_i[i]  = p.kon_cam    * s.Cai[i]    * ( p.Bmax_CaM     - s.CaM_i[i]             ) - p.koff_cam    * s.CaM_i[i];
	    var.dCaM_s[i]  = p.kon_cam    * s.Cai_sl[i] * ( p.Bmax_CaM     - s.CaM_s[i]             ) - p.koff_cam    * s.CaM_s[i];
	    var.dcsqn[i]   = p.kon_csqn   * s.CanSR[i]  * ( p.Bmax_Csqn    - s.csqn[i]              ) - p.koff_csqn   * s.csqn[i];
	    
	    s.Tn_CL[i]  += dt * var.dTn_CL[i];
	    s.Tn_CHc[i] += dt * var.dTn_CHc[i];
	    s.Tn_CHm[i] += dt * var.dTn_CHm[i];
	    s.CaM_i[i]  += dt * var.dCaM_i[i];
	    s.CaM_s[i]  += dt * var.dCaM_s[i];
	    s.csqn[i]   += dt * var.dcsqn[i];
	    
	    // Update Sodium concentration
	    s.Nai[i] += dt * p.Cm / ( 1e12 * p.F * ( p.Vcyto + p.Vsl ) ) * ( - ( var.If_Na[i] + var.Ist[i] + var.INaL[i] + var.INa[i] + var.INab[i] + 3 * var.INaK[i] + 3 * var.INCX[i] ) );
	    
	    // Update Potassium concentration
	    s.Ki[i]  += dt * p.Cm / ( 1e12 * p.F * ( p.Vcyto + p.Vsl ) ) * ( - ( var.IKr[i] + var.IKs[i] + var.Ito[i] + var.Isus[i] + var.ISK[i] + var.IK1[i] + var.If_K[i] + var.IKACh[i] - 2 * var.INaK[i] + var.IKb[i] + var.Istim[i] ) );
	    
	    // Update Calcium concentrations
	    s.Cai[i]    += dt * ( ( var.J_i_sl[i] * p.Vsl - var.J_SERCA[i] * p.VnSR ) / p.Vcyto - ( var.dCaM_i[i] + var.dTn_CL[i] + var.dTn_CHc[i] ) );
	    s.Cai_sl[i] += dt * ( p.Cm / ( 2 * 1e12 * p.F * p.Vsl ) * ( - ( var.ICaL[i] + var.ICaT[i] + var.ICab[i] + var.ICaD[i] - 2 * var.INCX[i] ) ) + var.J_rel[i] * p.VjSR / p.Vsl - ( var.J_i_sl[i] + var.dCaM_s[i] ) );
	    s.CanSR[i]  += dt * ( var.J_SERCA[i] - var.J_jsr_nsr[i] * p.VjSR / p.VnSR );
	    s.CajSR[i]  += dt * ( var.J_jsr_nsr[i] - ( var.J_rel[i] + var.dcsqn[i] ) );
    	}
}



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void write_outputs(std::ostream& out, State_variables s, Model_variables v, double t, int n, int i)
{
	//double mean_Cai = 0;
	//double mean_Vm = 0;
	//for (int i = 0; i < n; i++)
	//{
	//	mean_Cai += s.Cai[i];
	//	mean_Vm  += s.Vm[i];
	//}
	//mean_Cai /= n;
	//mean_Vm  /= n;
	
	// 1-2
	out << t << " " << s.Vm[i] 															\
	// 3-5
	<< " " << s.INa_va[i]  << " " << s.INa_vi[i]  << " " << s.INa_vi_2[i]  										\
	// 6-8
	<< " " << s.INaL_va[i] << " " << s.INaL_vi[i] << " " << s.INaL_vi_2[i] 										\
	// 9
	<< " " << 0 							       										\
	// 10-11
	<< " " << s.ICaL_va[i] << " " << s.ICaL_vi[i]                          										\
	// 12-13
	<< " " << s.ICaD_va[i] << " " << s.ICaD_vi[i]                          										\
	// 14-15
	<< " " << s.ICaT_va[i] << " " << s.ICaT_vi[i]                          										\
	// 16-18
	<< " " << s.IKr_va[i]  << " " << s.IKr_va_s[i] << " " << s.IKr_vi[i]   										\
	// 19-20
	<< " " << s.Ito_vi[i]  << " " << s.Ito_va[i]                           										\
	// 21
	<< " " << s.If_va[i]						       										\
	// 22-23	
	<< " " << s.Ist_va[i]  << " " << s.Ist_vi[i]			       										\
	// 24
	<< " " << s.IKs_va[i]						       										\
	// 25
	<< " " << s.ISK_va[i]						       										\
	// 26-28
	<< " " << s.RyRr[i]    << " " << s.RyRi[i]     << " " << s.RyRo[i]     										\
	// 29-30
	<< " " << s.Nai[i]     << " " << s.Ki[i]			       										\
	// 31-34
	<< " " << s.Cai[i]     << " " << s.Cai_sl[i]   << " " << s.CanSR[i]    << " " << s.CajSR[i] 							\
	// 35-40
	<< " " << s.Tn_CL[i]   << " " << s.Tn_CHc[i]   << " " << s.Tn_CHm[i]   << " " << s.CaM_i[i]  << " " << s.CaM_s[i]   << " " << s.csqn[i]		\
	// 41-42
	<< " " << 0            << " " << 0														\
	// 43 
	<< " " << s.Vm_Phi[i]																\
	// 44-48
	<< " " << v.INa[i]     << " " << v.INaL[i]     << " " << v.ICaL[i]     << " " << v.ICaD[i]   << " " << v.ICaT[i]				\
	// 49-53
	<< " " << v.IK1[i]     << " " << v.IKr[i]      << " " << v.Ito[i]      << " " << v.Isus[i]   << " " << v.If[i]					\
	// 54-58
	<< " " << v.IKs[i]     << " " << v.INab[i]     << " " << v.IKb[i]      << " " << v.ICab[i]   << " " << v.INaK[i]				\
	// 59-63
	<< " " << v.INCX[i]    << " " << v.Ist[i]      << " " << v.ISK[i]      << " " << v.IKACh[i]  << " " << v.IGap_AV1[i]				\
	// 64-66
	<< " " << v.Itot[i]    << " " << v.IGap_AV[i]  << " " << v.Istim[i]										\
	// 67-72
	<< " " << 0	       << " " << v.Ishk_Phi[i] << " " << v.IKur_Phi[i] << " " << v.Ib_Phi[i] << " " << v.IK1_Phi[i] << " " << v.IGap_Phi[i] 	\
	// 73-74
	<< " " << v.Itot_Phi[i] << " " << v.Istim_Phi[i]												\
	// END
	<< std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void set_Macrophage_parameters_Mangoni(Parameters &p, Simulation &Sim)
{
    
    // Constants
    p.F_Phi    = 96487;	// [C/mmol]
    p.R_Phi    = 8314; 	// [J/(mmol K)]
    p.T_Phi    = 297; 	// [K]
    p.FoRT_Phi = p.F_Phi / ( p.R_Phi * p.T_Phi ); // [mV^-1]
    
    // Capacitance
    p.Cm_Phi = 18.32; 	// [pF]
    
    // External potassium
    p.Ke_Phi = 5.4; 	// [mM]
    p.EK_Phi = -79.362; // [mV] - Nernst Potential
    
    p.stimduration_Phi 	= 5;//1; 		// [ms]
    p.stimmag_Phi 	= 0;//-0.6e3 / p.Cm_Phi; 	// [pA/pF]
    
    // Macrophage characterisation
    p.N_Phi 		= 1; 		// [-] - Number of macrophages
    p.Phi_type 		= 0;//12;		// [-] - Type of Macrophage
    
    // Macrophage-cell interaction through gap
    
    p.ggap_m = new double[Sim.nbrecell];
    for (int i = 0; i < Sim.nbrecell; i++)
    {
    	if ( (i+1) % Sim.dcells_Macrophage != 0 )
    	{
    		p.ggap_m[i] = 0;
    	}
    	else
    	{
    		p.ggap_m[i] = 1.5;
    	}
    }
    
    // And other currents
    p.gshk_Phi = 0.015 / p.Cm_Phi; 	// [nS/pF]
    p.N_shk    = 74;              	// [-] - Number of Shaker-type channels
    p.gKur_Phi = 3e-7 / p.Cm_Phi * 1e6; // [nS/pF]
    // (gb_Phi, Eb_Phi) and (gK1_Phi,aK1_Phi and bK1_Phi) depend on the Phi_type. They are set up afterwards.
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void set_Macrophage_type_parameters_Mangoni(Parameters &p)
{
    if ( p.Phi_type == 0 )
    {
        p.gb_Phi   = 1.6e-7 / p.Cm_Phi * 1e6; 	// [nS/pF]
        p.Eb_Phi   = -10; // [mV]
        
        p.gK1_Phi  = 4.2e-7 / p.Cm_Phi * 1e6; 	// [nS mM^(1/2) / pF]
        p.aK1_Phi  = 0.91; 			// [-]
        p.bK1_Phi  = 1.09; 			// [-]
        
        p.gshk_Phi = 0; 			// No Ishk current for this Macrophage type
        p.gKur_Phi = 0; 			// No IKur current for this Macrophage type
    }
    else if ( p.Phi_type == 1 )
    {
        p.gb_Phi   = 2.2e-7 / p.Cm_Phi * 1e6; 	// [nS/pF]
        p.Eb_Phi   = 0; 			// [mV]
        
        p.gK1_Phi  = 7.3e-7 / p.Cm_Phi * 1e6; 	// [nS mM^(1/2) / pF]
        p.aK1_Phi  = 0.8; 			// [-]
        p.bK1_Phi  = 0.7; 			// [-]
        
        p.gKur_Phi = 0; 			// No IKur current for this Macrophage type
    }
    else if ( p.Phi_type == 2 )
    {
        p.gb_Phi   = 3.5e-7 / p.Cm_Phi * 1e6; 	// [nS/pF]
        p.Eb_Phi   = 8; 			// [mV]
        
        p.gK1_Phi  = 1.3e-6 / p.Cm_Phi * 1e6; 	// [nS mM^(1/2) / pF]
        p.aK1_Phi  = 0.72; 			// [-]
        p.bK1_Phi  = 0.96; 			// [-]
        
        p.gshk_Phi = 0; 			// No Ishk current for this Macrophage type
    }
    else if ( p.Phi_type == 12 )
    {
        p.gb_Phi   = 3.5e-7 / p.Cm_Phi * 1e6; 	// [nS/pF]
        p.Eb_Phi   = 8; 			// [mV]
        
        p.gK1_Phi  = 1.3e-6 / p.Cm_Phi * 1e6; 	// [nS mM^(1/2) / pF]
        p.aK1_Phi  = 0.72; 			// [-]
        p.bK1_Phi  = 0.96; 			// [-]
    }
    else
    {
        printf("ERROR: \"%d\" is not a valid Macrophage type for this model\n", p.Phi_type);
        exit(1);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void compute_IGap_Phi_Mangoni( Parameters &p , Model_variables &var , State_variables &s , Modifiers &Mod , int n )
{
	for (int i = 0; i < n; i++)
	{
    		var.IGap_AV1[i] = Mod.ggap_m * p.ggap_m[i] / p.Cm     * ( s.Vm[i]     - s.Vm_Phi[i] );
    		var.IGap_Phi[i] = Mod.ggap_m * p.ggap_m[i] / p.Cm_Phi * ( s.Vm_Phi[i] - s.Vm[i]     );
    	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void compute_Ib_Phi_Mangoni( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	for (int i = 0; i < n; i++)
	{
    		var.Ib_Phi[i] = p.gb_Phi * ( s.Vm_Phi[i] - p.Eb_Phi ); // [pA/pF]
    	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void compute_IK1_Phi_Mangoni( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	for (int i = 0; i < n; i++)
	{
    		var.IK1_Phi[i] = p.gK1_Phi * pow( p.Ke_Phi , 0.5 ) * ( s.Vm_Phi[i] - p.EK_Phi ) / ( p.aK1_Phi + exp( p.bK1_Phi * ( s.Vm_Phi[i] - p.EK_Phi ) * p.FoRT_Phi ) );
    	}
    
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void compute_Ishk_Phi_Mangoni( Parameters &p , Model_variables &var , State_variables &s , int n )
{
    double A_Phi = 127.7;  // [ms^-1]
    double B_Phi = 16.5;   // [ms^-1]
    double a_Phi = 3.96;   // [ms^-1]
    double b_Phi = 0.1;    // [ms^-1]
    double c_Phi = 0.0029; // [ms^-1]
    double d_Phi = 0.0008; // [ms^-1]
    double m_Phi = 11.1;   // [mV]
    double n_Phi = 26;     // [mV]
    double p_Phi = 1205.3; // [mV]
    double q_Phi = 3377.2; // [mV]
    
    double dt = p.dt;
    
    	for (int i = 0; i < n; i++)
	{
		double alpha_Phi = a_Phi * exp(   s.Vm_Phi[i] / m_Phi );
		double beta_Phi  = b_Phi * exp( - s.Vm_Phi[i] / n_Phi );
		double mu_Phi    = c_Phi * exp(   s.Vm_Phi[i] / p_Phi );
		double phi_Phi   = d_Phi * exp( - s.Vm_Phi[i] / q_Phi );

		var.dShk_C0_Phi[i] = - 4 * alpha_Phi * s.Shk_Phi_C0[i] + beta_Phi * s.Shk_Phi_C1[i];
		var.dShk_C1_Phi[i] = 4 * alpha_Phi * s.Shk_Phi_C0[i] - ( 3 * alpha_Phi + beta_Phi ) * s.Shk_Phi_C1[i] + 2 * beta_Phi * s.Shk_Phi_C2[i];
		var.dShk_C2_Phi[i] = 3 * alpha_Phi * s.Shk_Phi_C1[i] - ( 2 * alpha_Phi + 2 * beta_Phi ) * s.Shk_Phi_C2[i] + 3 * beta_Phi * s.Shk_Phi_C3[i];
		var.dShk_C3_Phi[i] = 2 * alpha_Phi * s.Shk_Phi_C2[i] - ( alpha_Phi + 3 * beta_Phi ) * s.Shk_Phi_C3[i] + 4 * beta_Phi * s.Shk_Phi_C4[i];
		var.dShk_C4_Phi[i] = alpha_Phi * s.Shk_Phi_C3[i] - ( A_Phi + 4 * beta_Phi ) * s.Shk_Phi_C4[i] + B_Phi * s.Shk_Phi_O[i];
		var.dShk_O_Phi[i]  = A_Phi * s.Shk_Phi_C4[i] - ( mu_Phi + B_Phi ) * s.Shk_Phi_O[i] + phi_Phi * s.Shk_Phi_I[i];
		var.dShk_I_Phi[i]  = mu_Phi * s.Shk_Phi_O[i] - phi_Phi * s.Shk_Phi_I[i];

		s.Shk_Phi_C0[i] += dt * var.dShk_C0_Phi[i]; 
		s.Shk_Phi_C1[i] += dt * var.dShk_C1_Phi[i]; 
		s.Shk_Phi_C2[i] += dt * var.dShk_C2_Phi[i]; 
		s.Shk_Phi_C3[i] += dt * var.dShk_C3_Phi[i]; 
		s.Shk_Phi_C4[i] += dt * var.dShk_C4_Phi[i]; 
		s.Shk_Phi_O[i]  += dt * var.dShk_O_Phi[i]; 
		s.Shk_Phi_I[i]  += dt * var.dShk_I_Phi[i]; 

		var.Ishk_Phi[i] = p.gshk_Phi * p.N_shk * s.Shk_Phi_O[i] * ( s.Vm_Phi[i] - p.EK_Phi );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void compute_IKur_Phi_Mangoni( Parameters &p , Model_variables &var , State_variables &s , int n )
{
	double dt = p.dt;
	for (int i = 0; i < n; i++)
	{
		var.IKur_Phi_va_ss[i]  = 1.0 / ( 1.0 + exp( ( s.Vm_Phi[i] + 6 ) / 86 ) );
		var.IKur_Phi_va_tau[i] = 3.6e-4 + 0.0066 / ( 1.0 + exp( ( s.Vm_Phi[i] + 5 ) / 1.2 ) );

		var.IKur_Phi_vi_ss[i]  = 1.0 / ( 1.0 + exp( ( s.Vm_Phi[i] + 7.5 ) / 18.8 ) );
		var.IKur_Phi_vi_tau[i] = 2.2 + 0.43 / ( 1.0 + exp( ( s.Vm_Phi[i] + 60 ) / 1 ) );

		s.IKur_Phi_va[i] = rush_larsen( s.IKur_Phi_va[i] , var.IKur_Phi_va_ss[i] , var.IKur_Phi_va_tau[i] , dt );
		s.IKur_Phi_vi[i] = rush_larsen( s.IKur_Phi_vi[i] , var.IKur_Phi_vi_ss[i] , var.IKur_Phi_vi_tau[i] , dt );

		var.IKur_Phi[i] = p.gKur_Phi * s.IKur_Phi_va[i] * s.IKur_Phi_vi[i] * ( s.Vm_Phi[i] - p.EK_Phi ); 
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void setup_arguments(int Narg , char *argin[] , Parameters &p, Simulation &Sim, Modifiers &Mod)
{
	int counter = 1;
	bool valid_argument;
	while (counter < Narg)
	{
		valid_argument = false;
		if ( strcmp(argin[counter], "initial_condition_default") == 0 )
		{
			Sim.initial_condition_default = argin[counter + 1];
			if ( strcmp(Sim.initial_condition_default, "On") != 0 && strcmp(Sim.initial_condition_default, "Off") != 0 )
			{
				printf("ERROR: initial_condition_default can only be On or Off, but you are setting it as %s\n", Sim.initial_condition_default);
				exit(1);
			}
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "BCL") == 0 )
		{
			Sim.BCL = atof(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "Ncells") == 0 )
		{
			Sim.nbrecell = atoi(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "Macrophage_type") == 0 || strcmp(argin[counter], "Phi_type") == 0 )
		{
			p.Phi_type = atoi(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "Macrophage_coupling") == 0)
		{
			Sim.Macrophage_coupling = argin[counter + 1];
			counter ++;
			valid_argument = true;
			if ( strcmp(Sim.Macrophage_coupling,"On") != 0 && strcmp(Sim.Macrophage_coupling,"Off") != 0 )
			{
				printf("ERROR: Macrophage_coupling can only be On or Off, but you are setting it as %s\n", Sim.Macrophage_coupling);
				exit(1);
			}
		}
		if ( strcmp(argin[counter], "Total_time") == 0 )
		{
			Sim.Total_time = atof(argin[counter+1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "Ncells_stim") == 0 )
		{
			Sim.Ncells_stim = atoi(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "dcells_Macrophage") == 0 )
		{
			Sim.dcells_Macrophage = atoi(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "Ggap_scale") == 0 )
		{
			Mod.ggap = atof(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "Ggapm_scale") == 0 )
		{
			Mod.ggap_m = atof(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "Reference") == 0 )
		{
			Sim.Folder_reference = argin[counter + 1];
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "N_Phi") == 0 )
		{
			p.N_Phi = atoi(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "version_default") == 0 )
		{
			Sim.version_default = atoi(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "Time_Application_Circ") == 0 )
		{
			Sim.Time_Application_Circ = atof(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "Increment_Cav") == 0 )
		{
			Sim.factor_Cav = atof(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "Increment_Kr") == 0 )
		{
			Sim.factor_Kr = atof(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}
		if ( strcmp(argin[counter], "Increment_KAch") == 0 )
		{
			Sim.factor_KAch = atof(argin[counter + 1]);
			counter ++;
			valid_argument = true;
		}

		if ( !valid_argument )
		{
			printf("ERROR: Argument %s is not valid!\n",argin[counter]);
			exit(1);
		}

		counter ++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void Simulation_defaults(Simulation &Sim)
{
	Sim.initial_condition_default 	= "On";
	Sim.Macrophage_coupling 	= "On";
	Sim.BCL 			= 133.33; 	// ms
	Sim.Total_time 			= 5000; 	// ms
	Sim.nbrecell 			= 50;
	Sim.n_states			= 42;
	Sim.t_save 			= 1+1e-10;
	Sim.t_print			= 10+1e-10;
	Sim.Folder_reference 		= "Outputs";
	Sim.Ncells_stim			= 5;
	Sim.dcells_Macrophage		= 10;
	Sim.version_default		= 1;
	Sim.Time_Application_Circ 	= 2000;		// ms
	Sim.factor_Cav = 1;
	Sim.factor_Kr = 1;
	Sim.factor_KAch = 1;
}

void Modifiers_defaults(Modifiers &Mod)
{
	Mod.ggap 	= 1;
	Mod.ggap_m 	= 1;
}

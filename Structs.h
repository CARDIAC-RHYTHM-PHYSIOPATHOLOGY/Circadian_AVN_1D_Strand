#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

// Parameters ===================================================================================\\|
struct Parameters{

	// Global control variables ========================================\\|
	double      dt;                     // Integration time-step

	// Constants =======================================================\\|
	double R;                   // J mol^-1 K^-1
	double F;                   // C mmol-1
	double T;                   // K
	double FoRT;                // F/RT
	// End Constants ===================================================//|

	// Temperature coefficient Q10
	double Q10; 		// (dimensionless)

	// Stimulus parameters =============================================\\|
	double stimduration;        // duration of applied stimulus (ms)
	double stimmag;             // magnitude of applied stimulus (A/F || pA/pF)
	// End Stimulus parameters =========================================//|

	// Cell structure parameters =======================================\\|
	double Cm;                  // Membrane capacitance                         (pF)
	double Cm_surf;             // Membrane capacitance per unit area           

	double Vcell;               // volume of whole cell (um^3)
	double Vcyto;               // volume of intracellular Ca2+ space
	double VjSR;                // volume of jSR / release Ca2+ space
	double VnSR;                // volume of nSR / uptake Ca2+ space
	double Vsl;                 // Volume of intracellular sub-sarcolemmal space

	// Ion currents ====================================================\\|
	// Conductances
	double gNa;                 // Conductance of fast-sodium current           (S/mF)
	double gNaL;                // Conductance of late-sodium current           (S/mF)
	double gto;                 // Conductance of transient-outward K+ current  (S/mF)
	double gCaL;                // Conductance of L-type ca current             (S/mF)
	double gKr;                 // Conductance of rapid delayed K+ current      (S/mF)
	double gKs;                 // Conductance of slow delayed K+ current       (S/mF)
	double gK1;                 // Conductance of time-independent K+ current   (S/mF)
	double gNab;                // Conductance of background sodium current     (S/mF)
	double gCab;                // Conductance of background calcium current    (S/mF)
	double gKb;                 // Conductance of background potassium current  (S/mF)
	double gKACh;               // Conductance of ACh-activated K+ current      (S/mF)
	double gf;                  // Conductance of "funny" current               (S/mF)
	double gCaD;                // Conductance of L-type Ca2+ current (Cav1.3)  (S/mF)
	double gCaT;                // Conductance of T-type Ca2+ current (Cav3.1)  (S/mF)
	double gsus;                // Conductance of K+ sustained outward current  (S/mF)
	double gst;                 // Conductance of K+ sustained inward current   (S/mF)
	double gSK;                 // Conductance of Ca2+-dependent K+ current     (S/mF)

	double FKr;                 // Fraction of IKr slow gates                   (dimensionless)
	// End Ion currents ================================================//|

	// Pumps and exchangers ============================================\\|
	// NCX params
	double INCX_bar;            // Maximal current scale factor for NCX         (pA/pF) or (um^3.uM.ms^-1)
	double INCX_kNao;           // [Na+]o saturation constant for INCX          (mM)
	double INCX_kCao;           // [Ca2+]o saturation constant for INCX         (mM)
	double INCX_gamma;          // Voltage dependence factor for INCX           (dimensionless)
	double INCX_ksat;           // Saturation constant                          (dimensionless)
	double INCX_alpha;          // INCX reverse mode scale                      (dimensionless)

	// NaK params
	double INaK_bar;            // Maximal current scale factor for INaK        (pA/pF)
	double INaK_kK;             // Half-Saturation constant for Ko INaK         (mM)
	double INaK_kNa;            // Half-saturation constant for Nai INaK        (mM)

	// End Pumps and exchangers ========================================//|

	// Concentrations ==================================================\\|
	// Many may also be updated state variables; the param in that case
	// becomes the IC for the state variable
	double Nao;                 // Extracellular sodium concentration (mM)
	double Ko;                  // Extracellular potassium concentration (mM)
	double Cao;                 // Extracellular calcium concentration (mM)
	// End concentrations ==============================================//|

	// Ca2+ handling ===================================================\\|
	// General/common =========================\\|

	double J_SERCA_max;         // Maximal flux rate of intracellular Ca2+ uptake   (mM/ms) or (uM/ms)
	double J_jsr_nsr_tau;       // Time constant of transfer between jsr and nsr    (ms)
	double J_i_sl_tau;          // Time constant of transfer between cyt and sl     (ms)
	// End General/common =====================//|


	// Buffering ==============================\\|

	double Mgi;
	double kon_tnchca;          // ms^-1 mM^-1
	double koff_tnchca;         // ms^-1
	double Bmax_TnChigh;        // mM
	double kon_tnchmg;          // ms^-1 mM^-1
	double koff_tnchmg;         // ms^-1
	double kon_tncl;            // ms^-1 mM^-1
	double koff_tncl;           // ms^-1
	double Bmax_TnClow;         // mM
	double Bmax_CaM;            // mM
	double kon_cam;             // ms^-1 mM^-1
	double koff_cam;            // ms^-1
	double Bmax_Csqn;           // mM
	double kon_csqn;            // ms^-1 mM^-1
	double koff_csqn;           // ms^-1


	// End Buffering ==========================//|

	// Grandi-Bers: Transport - SR =========================\\|
	double ks;                  // ms^-1
	double Kmf;                 // mM
	double Kmr;                 // mM
	double hillSRCaP;
	double koCa;                // ms^-1 mM^-1
	double kiCa;                // ms^-1 mM^-1
	double kim;                 // ms^-1
	double kom;                 // ms^-1
	double ec50SR;              // mM
	double MaxSR;               // mM (?)
	double MinSR;               // mM (?)
	// End Grandi-Bers: Transport - SR ======================//|
	double HSR;                 // (dimensionless) - Exponent
	// End Ca2+ handling ===============================================//|


	// Macrophage ===============================================\\|
    
	// Constants
	double F_Phi;    // (C/mmol)
	double R_Phi;    // (J/(mmol K))
	double T_Phi;    // (K)
	double FoRT_Phi; // (mV^-1)

	// Capacitance
	double Cm_Phi; // Macrophage capacitance                      (pF)

	// Potassium electromechanical
	double Ke_Phi; // Extracellular concentrtion of Potassium     (mM)
	double EK_Phi; // Nernst Potential of Potassium in Macrophage (mV)

	// Excitation
	double stimduration_Phi; // (ms)
	double stimmag_Phi;      // (pA/pF)

	// Macrophage characterisation
	int N_Phi;    // Number of macrophages (dimensionless)
	int Phi_type; // Type of macrophage    (dimensionless)

	// Currents
	double *ggap_m;  // Conductance of IGap_Phi and IGap_AV1 (nS/pF)
	double ggap;	 // Conductance of cell-cell coupling IGap_AV
	double gshk_Phi; // Conductance of Ishk_Phi 		(nS/pF)
	double gKur_Phi; // Conductance of IKur_Phi 		(nS/pF)
	double gb_Phi;   // Conductance of Ib_Phi 		(nS/pF)
	double gK1_Phi;  // Conductance of IK1_Phi 		(nS/pF)

	int N_shk;       // Number of channels for Ishk_Phi     (dimensionless)
	double Eb_Phi;   // Reverse potential for Ib_Phi        (mV)
	double aK1_Phi;  //                                     (dimensionless)
	double bK1_Phi;  //                                     (dimensionless)
        
    // End Macrophage ===========================================//|
    
    // Distance between cells
    
    double deltax;
	double Diff; //(mm/ms)

};
// End Parameters ===============================================================================//|

// State_variables =============================================================================\\|
struct State_variables{

	double *Vm;

	double *Nai;
	double *Ki;
	double *Cai;
	double *Cai_sl;
	double *CanSR;
	double *CajSR;
	double *Nao;
	double *Ko;
	double *Cao;

	double *CaM_i;
	double *CaM_s;
	double *Tn_CL;
	double *Tn_CHc;
	double *Tn_CHm;
	double *csqn;

	double *RyRr;
	double *RyRo;
	double *RyRi;

	double *INa_va;
	double *INa_vi_1;
	double *INa_vi_2;
	double *INa_vi;
	double *INaL_va;
	double *INaL_vi_1;
	double *INaL_vi_2;
	double *INaL_vi;
	double *ICaL_va;
	double *ICaL_vi;
	double *ICaD_va;
	double *ICaD_vi;
	double *ICaT_va;
	double *ICaT_vi;
	double *IKr_va;
	double *IKr_va_s;
	double *IKr_vi;
	double *Ito_vi;
	double *Ito_va;
	double *If_va;
	double *Ist_va;
	double *Ist_vi;
	double *IKs_va;
	double *ISK_va;


	// Macrophages
	double *Vm_Phi;
	double *IKur_Phi_va;
	double *IKur_Phi_vi;
	double *Shk_Phi_C0;
	double *Shk_Phi_C1;
	double *Shk_Phi_C2;
	double *Shk_Phi_C3;
	double *Shk_Phi_C4;
	double *Shk_Phi_O;
	double *Shk_Phi_I;

};
// End State_variables =========================================================================//|

struct Model_variables{
	// Reversal potentials
	double *ENa;
	double *EK;
	double *EKs_BM;
	double *ECa;
	double *ECa_sl;
	
	double *Itot;
	
	double *INa_va_ss;
	double *INa_va_tau;
	double *INa_vi_1_ss;
	double *INa_vi_2_ss;
	double *INa_vi_1_tau;
	double *INa_vi_2_tau;
	double *INa;
	
	double *INaL_va_ss;
	double *INaL_va_tau;
	double *INaL_vi_ss;
	double *INaL_vi_tau;
	double *INaL_vi_2_tau;
	double *INaL;
	
	double *ICaL_va_tau;
	double *ICaL_va_ss;
	double *ICaL_vi_tau;
	double *ICaL_vi_ss;
	double *ICaL;
	
	double *ICaD_va_tau;
	double *ICaD_va_ss;
	double *ICaD_vi_tau;
	double *ICaD_vi_ss;
	double *ICaD;
	
	double *ICaT_va_tau;
	double *ICaT_va_ss;
	double *ICaT_vi_tau;
	double *ICaT_vi_ss;
	double *ICaT;
	
	double *IK1;
	
	double *IKr_va_ss;
	double *IKr_va_tau;
	double *IKr_va_s_tau;
	double *IKr_vi_ss;
	double *IKr_vi_tau;
	double *IKr;
	
	double *Ito_va_ss;
	double *Ito_va_tau;
	double *Ito_vi_ss;
	double *Ito_vi_tau;
	double *Ito;
	double *Isus;
	
	double *IKs_va_al;
	double *IKs_va_bet;
	double *IKs_va_ss;
	double *IKs_va_tau;
	double *IKs;
	
	double *If_va_ss;
	double *If_va_tau;
	double *If_Na;
	double *If_K;
	double *If;
	
	double *INab;
	double *IKb;
	double *ICab;
	
	double *INaK;
	
	double *INCX;
	
	double *Ist_va_ss;
	double *Ist_va_tau;
	double *Ist_vi_ss;
	double *Ist_vi_tau;
	double *Ist;
	
	double *ISK_va_ss;
	double *ISK_va_tau;
	double *ISK;
	
	double *IKACh;
	
	double *J_jsr_nsr;
	double *J_i_sl;
	double *dTn_CL;
	double *dTn_CHc;
	double *dTn_CHm;
	double *dCaM_i;
	double *dCaM_s;
	double *dcsqn;
	
	double *kCaSR;
	double *koSRCa;
	double *kiSRCa;
	double *RI;
	double *J_rel;
	
	double *J_SERCA;
	
	double *Istim;
	double *Istim_Phi;
	
	double *Itot_Phi;
	
	double *IGap_AV1;
	double *IGap_Phi;
	
	double *Ib_Phi;
	
	double *IK1_Phi;
	
	double *dShk_C0_Phi;
	double *dShk_C1_Phi;
	double *dShk_C2_Phi;
	double *dShk_C3_Phi;
	double *dShk_C4_Phi;
	double *dShk_O_Phi;
	double *dShk_I_Phi;
	double *Ishk_Phi;
	
	double *IKur_Phi_va_ss;
	double *IKur_Phi_va_tau;
	double *IKur_Phi_vi_ss;
	double *IKur_Phi_vi_tau;
	double *IKur_Phi;
	
	//double *IGap_AV;
	double *D2vodx;
	
};

struct Simulation{
	const char *initial_condition_default;
	double BCL;
	double Total_time;
	const char *Macrophage_coupling;
	int nbrecell;
	int n_states;
	double t_save;
	double t_print;
	const char *Folder_reference;
	int Ncells_stim;
	int dcells_Macrophage;
	int version_default;
	double Time_Application_Macro;
    double factor_Cav;
	double factor_Kr;
	double factor_KAch;
};

struct Modifiers{
	float ggap;
	float ggap_m;
};

#endif

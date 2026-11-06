#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <time.h>
#include <chrono>

#include "Structs.h"
#include "functions_Mangoni1D.cpp"

using namespace std;

int main(int argc, char *argv[])
{
	// Set simulation defaults
	Simulation Sim;
	Simulation_defaults(Sim);
	
	auto starting_time = std::chrono::high_resolution_clock::now();
	// Set parameters
	Parameters Params;
	set_parameters_mAVNM_BM(Params);
	
	Modifiers Mod;
	Modifiers_defaults(Mod);
	setup_arguments(argc, argv, Params, Sim, Mod);
	// Initialise state variables and set initial conditions
	State_variables State;
	if (strcmp(Sim.initial_condition_default,"On") == 0)
	{
		if (Sim.version_default == 1)
		{
			set_default_initial_conditions(State, Params, Sim);
		}
		else if (Sim.version_default == 2)
		{
			set_default_initial_conditions_v2(State, Params, Sim);
		} 
		else
		{
			printf("ERROR: No valid version of initial conditions!\n");
			exit(1);
		}
	}
	else
	{
		const char *initial_filename = "initial_conditions.csv";
		set_initial_conditions(State, initial_filename , Params, Sim);
	}
	
	// Set (Macrophage) parameters
	set_Macrophage_parameters_Mangoni(Params,Sim);
	set_Macrophage_type_parameters_Mangoni(Params);
	
	// Initialise model variables
	Model_variables Var;
	allocate_variables(Var, Sim.nbrecell);
	
	
	std::ofstream *output_file;
	output_file = new std::ofstream[Sim.nbrecell];
	static char mkdirectory[512];
	sprintf(mkdirectory, "mkdir -p %s", Sim.Folder_reference);
	system(mkdirectory);
	for (int i = 0; i < Sim.nbrecell; i++)
	{
		static char mkfile[512];
		sprintf(mkfile, "%s/Output_%d.txt", Sim.Folder_reference, i);
		output_file[i].open(mkfile);
	}
	
	double t_beat; // time of the beat
	double t; // time
	int i_save = Sim.t_save/Params.dt;
	int i_print = Sim.t_print/Params.dt;
	int i_sim = 0;
	// Istim
	t_beat = 0;
	
	// Time loop!
	for ( t = 0; t < Sim.Total_time ; t += Params.dt )
	{
		
		// Stimulus current
		double istim = (t_beat <= Params.stimduration) ? Params.stimmag : 0;
		double istim_phi = (t_beat <= Params.stimduration_Phi) ? Params.stimmag_Phi : 0;

		for (int i = 0; i < Sim.nbrecell; i++)
		{
			Var.Istim[i] = (i < Sim.Ncells_stim) ? istim : 0; // only stimulated first Ncells_stim cells.
			Var.Istim_Phi[i] = istim_phi;
		}
		
		// Compute currents
		compute_reversal_potentials(Params, Var, State, Sim.nbrecell);
		compute_INa_mAVNM_BM( Params , Var , State, Sim.nbrecell );
		compute_INaL_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_ICaL_mAVNM_BM( Params, Var , State , Sim.nbrecell ,Sim.factor_Cav);
		compute_ICaD_mAVNM_BM( Params, Var , State , Sim.nbrecell ,Sim.factor_Cav);
		compute_ICaT_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_IK1_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_IKr_mAVNM_BM( Params, Var , State , Sim.nbrecell ,Sim.factor_Kr);
		compute_Ito_Isus_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_IKs_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_If_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_INab_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_IKb_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_ICab_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_INaK_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_INCX_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_Ist_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_ISK_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		compute_IKACh_mAVNM_BM( Params, Var , State , Sim.nbrecell ,Sim.factor_KAch);
		
		if ( ( strcmp(Sim.Macrophage_coupling,"On") == 0 ) && ( t >= Sim.Time_Application_Macro ) )
		{
			compute_IGap_Phi_Mangoni( Params , Var , State , Mod , Sim.nbrecell );
			compute_Ib_Phi_Mangoni( Params , Var , State , Sim.nbrecell );
			compute_IK1_Phi_Mangoni( Params , Var , State , Sim.nbrecell );
			compute_Ishk_Phi_Mangoni( Params , Var , State , Sim.nbrecell );
			compute_IKur_Phi_Mangoni( Params , Var , State , Sim.nbrecell );
		}
		
		// Total current
		for (int i = 0; i < Sim.nbrecell; i++)
		{
			Var.Itot[i] = Var.INa[i] + Var.INaL[i] + Var.ICaL[i] + Var.ICaD[i] + Var.ICaT[i] + Var.IK1[i] + Var.IKr[i] + Var.Ito[i] + Var.Isus[i] + Var.If[i] + Var.IKs[i] + Var.INab[i] + Var.IKb[i] + Var.ICab[i] + Var.INaK[i] + Var.INCX[i] + Var.Ist[i] + Var.ISK[i] + Var.IKACh[i] + Params.N_Phi * Var.IGap_AV1[i];
			
			Var.Itot_Phi[i] = Var.Ishk_Phi[i] + Var.IKur_Phi[i] + Var.Ib_Phi[i] + Var.IK1_Phi[i] + Var.IGap_Phi[i];
			
			if (i == 0)
			{
				//Var.IGap_AV[i] =  Mod.ggap * (Params.ggap/Params.Cm ) * ( ( State.Vm[i+1] - State.Vm[i] )/Params.deltax* Params.deltax);
				Var.D2vodx[i] = Mod.ggap*(Params.Diff) * ( ( State.Vm[i+1] - State.Vm[i] )/Params.deltax* Params.deltax);
			}
			else if (i == Sim.nbrecell - 1)
			{
				//Var.IGap_AV[i] =  Mod.ggap * (Params.ggap/Params.Cm)  * ( ( - State.Vm[i] + State.Vm[i-1] )/Params.deltax* Params.deltax);
				Var.D2vodx[i] = Mod.ggap*(Params.Diff) * ( ( - State.Vm[i] + State.Vm[i-1] )/Params.deltax* Params.deltax);

			}
			else
			{
				//Var.IGap_AV[i] =  Mod.ggap * (Params.ggap/Params.Cm )  * ( ( State.Vm[i+1] + State.Vm[i-1] - 2 * State.Vm[i] )/Params.deltax* Params.deltax);
				Var.D2vodx[i] = Mod.ggap*(Params.Diff)  * ( ( State.Vm[i+1] + State.Vm[i-1] - 2 * State.Vm[i] )/Params.deltax* Params.deltax); 
			}
		} 
		
		// Compute homeostasis
		
		compute_homeostasis_mAVNM_BM( Params, Var , State , Sim.nbrecell );
		
		// Update voltage
		for (int i = 0; i < Sim.nbrecell; i++)
		{
			//State.Vm[i] = State.Vm[i] + Params.dt * ( - ( Var.Itot[i] + Var.Istim[i] ) + Var.IGap_AV[i] );
			State.Vm[i] = State.Vm[i] + Params.dt * ( - ( Var.Itot[i] + Var.Istim[i] ) + Var.D2vodx[i] );

			State.Vm_Phi[i] = State.Vm_Phi[i] + Params.dt * ( - ( Var.Itot_Phi[i] + Var.Istim_Phi[i] ) );
		}
		// Update time in beat and print
		t_beat = t - Sim.BCL * (int)(t/Sim.BCL);


		if (i_sim % i_print == 0)
		{
			printf("time :   %f msec \n",t);
			
		}

		
		// Write outputs
		if (i_sim % i_save == 0 )
		{
			for (int i = 0; i < Sim.nbrecell; i++)
			{
				write_outputs(output_file[i], State, Var, t, Sim.nbrecell, i);
			}
		}
		i_sim += 1;
		
	}

	auto final_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::chrono::minutes::period> duration = final_time - starting_time;
	printf("Elapsed time: %f minutes\n", duration.count());
	
	
	

	return 0;
};

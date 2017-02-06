#include "DDMRootManager.hh"

DDMRootManager* the_root_manager;
TTree* energyLoss_tree;

void DDMRootManager::CreateRootManager(G4String filename)
{
	the_root_manager = new DDMRootManager(filename);
}

DDMRootManager* DDMRootManager::GetRootManager()
{
	return the_root_manager;
}

void DDMRootManager::DestroyRootManager()
{
	delete the_root_manager;
}

DDMRootManager::DDMRootManager(G4String filename)
{
	root_file = new TFile(filename.c_str(),"RECREATE");
}

void DDMRootManager::InitialiseTree(G4String treename1)
{
	energyLoss_tree = new TTree("T", treename1.c_str());

	// # BRANCH
	energyLoss_tree -> Branch("energyLoss_data",&TimeStepData_mng, "Time/D:posx/D:posy/D:posz/D:IonisationEnergy_ev/D");
}

void DDMRootManager::FillTree_TimeStepData(G4double input_time, G4double input_x, G4double input_y, G4double input_z, G4double input_energy)
{
	TimeStepData_mng[0]=input_time;
	TimeStepData_mng[1]=input_x;
	TimeStepData_mng[2]=input_y;
	TimeStepData_mng[3]=input_z;
	TimeStepData_mng[4]=input_energy;

	energyLoss_tree->Fill();
}

void DDMRootManager::CloseTree()
{
	energyLoss_tree->Write();
	
	delete energyLoss_tree;
}

DDMRootManager::~DDMRootManager()
{
	root_file->Write();
	delete root_file;
}

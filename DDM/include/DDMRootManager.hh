#ifndef ROOT_MANAGER_HH
#define ROOT_MANAGER_HH

#include "TFile.h"
#include "TTree.h"
#include "globals.hh"
#include <string>
#include "G4String.hh"
#include "TH1D.h"
#include "TH2I.h"
#include "TH3I.h"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "TGraph.h"
#include "TGraph2D.h"
//#include "TCanvas.h"
#include <sstream>
#include <fstream>
#include "TFitResult.h"
#include "G4PhysicalConstants.hh"
#include "TLine.h"
#include "Randomize.hh"

using namespace std;

class DDMRootManager
{
	private:
		TFile* root_file;
		// Define _mng variables/arrays as needed.
		
		Bool_t UseStreamlining_mng = false;
		Bool_t SaveToStorage_mng = false;
	
		// arrays for filling data
		Double_t TimeStepData_mng[5] = {0};
		Double_t ElectronData_mng[3] = {0};
		Double_t RecoData_mng[4] = {0};
		Double_t RecoResults_mng[11] = {0};
		Double_t RecoResultsCamera_mng[9] = {0};
	
		// detector construction information
		Double_t DriftVelocity_mng = 0;
		Double_t ElectricField_mng = 0;
		Double_t Temperature_mng = 0;
		Double_t GasPressure_mng = 0;
		Double_t TankHeight_mng = 0;
	
		// counters / yields
		Int_t EventCounter_mng = -1;
		Int_t ElectronCounter_mng = 0;
		Int_t SecondaryScintCounter_mng = 0;
		Double_t SecondaryScintYield_mng = 0;
		//Double_t InitialMomentum_mng[4] = {0};
	
		Bool_t IsFirstStep_mng = false;
	
		// trajectory angles
		Double_t TrueTheta_mng = 0;
		Double_t TruePhi_mng = 0;
		Double_t CameraTanPhi_mng = 0;
	
		// camera variables
		Int_t CameraResolution_mng = 1000;
		Double_t TimeResolution_mng = 0;
	
		Double_t LensRadius_mng = 85.0*mm;
		Double_t LensCentreX_mng = 0.0*mm;
		Double_t LensCentreY_mng = 0.0*mm;
		Double_t ScintToLensDistance_mng = 0.5*m;
		Double_t LensMag_mng = LensRadius_mng/(1.0*m);
	
		Double_t SensorX_mng = LensRadius_mng;
		Double_t SensorEffectiveX_mng = SensorX_mng/LensMag_mng;
		Double_t SensorY_mng = LensRadius_mng;
		Double_t SensorEffectiveY_mng = SensorY_mng/LensMag_mng;
		
		
	public:
		static void CreateRootManager();
		static DDMRootManager* GetRootManager();
		static void DestroyRootManager();

		DDMRootManager();
	
		void CreateOutputFile(G4String filename);
		void ReadParameterFile(G4String filename);

		void InitialiseTrees();// Add more trees as arguments if desired.
		void InitialiseResultsTree();

		//void FillTree(); Make more of these (with specific names and the required parameters) for the individual branches as needed.
		void FillTree_TimeStepData(Double_t input_time, Double_t input_x, Double_t input_y, Double_t input_z, Double_t input_energy);
		void FillTree_ElectronData(Double_t input_time, Double_t input_x, Double_t input_y);
		//void FillHist_ElectronGen(Double_t input_x, Double_t input_y, Double_t input_z);
		void FillTree_RecoTrack(Double_t input_x, Double_t input_y, Double_t input_z, Double_t input_time);
		//void FillHist_RecoTrack(Double_t input_x, Double_t input_y, Double_t input_z);
		void FillGraph_RecoTrackXY(Double_t input_x, Double_t input_y);
		void FillGraph_RecoTrackXZ(Double_t input_x, Double_t input_z);
		void FillGraph_RecoTrackYZ(Double_t input_y, Double_t input_z);
		void FillGraph_RecoTrack(Double_t input_x, Double_t input_y, Double_t input_z);
		void FillTree_RecoResults(Double_t input_tanphi, Double_t input_tantheta_xz, Double_t input_tantheta_yz, Double_t input_tanphi_scint);
		void FillTree_RecoResultsCamera(Double_t input_phi, Double_t input_theta, Double_t input_headtail, Double_t input_deviation,
					        Double_t input_deltaPhi, Double_t input_deltaTheta);
		void FillGraph_ElectronGen(Double_t input_x, Double_t input_y, Double_t input_z);
		void FillHist_DirectScint(Double_t input_x, Double_t input_y);
		void FillHist_Camera(Double_t input_x, Double_t input_y);
		void FillHist_CameraXZ(Double_t input_x, Double_t input_z);
		void FillHist_CameraYZ(Double_t input_y, Double_t input_z);
		Double_t FitCameraHist(TH2I* input_hist, Double_t* fitError);
		Double_t HeadTail(Double_t input_grad, Double_t input_skewnessX, Double_t input_headTail);
	
		void FinaliseEvent();
		void CloseResultsTree();
	
		//void NewBranch();
	
		Double_t CalculateTanThetaFromXZ(Double_t input_tanphi, Double_t input_tanalpha);
		Double_t CalculateTanThetaFromYZ(Double_t input_tanphi, Double_t input_tanbeta);
	
		G4double CalculateSigmaT(Double_t input_time, Double_t input_mu, Double_t input_T);
		G4double CalculateSigmaL(Double_t input_time, Double_t input_mu, Double_t input_T);
	
		G4double CalculateDriftVelocity();
		G4double CalculateSecondaryScintYield(Double_t input_avalancheField);
		
		Double_t CalculateVectorAngle(Double_t input_phi, Double_t input_theta);

		// define Get and Set methods for each _mng variable: can be defined inline.
	
		void ActivateStreamlining() {UseStreamlining_mng = true;}
		Bool_t IsStreamliningOn() {return UseStreamlining_mng;}
		Bool_t IsStreamliningOff() {return !UseStreamlining_mng;}
	
		void ActivateSaveToStorage() {SaveToStorage_mng = true;}
		Bool_t SavingToStorage() {return SaveToStorage_mng;}
	
		Int_t GetEventCounter() {return EventCounter_mng;}
		
		//void SetDriftVelocity(Double_t input) {DriftVelocity_mng = input;}
		Double_t GetDriftVelocity() {return DriftVelocity_mng;}
	
		Double_t GetSecondaryScintYield() {return SecondaryScintYield_mng;}
	
		void SetTankHeight(Double_t input) {TankHeight_mng = input;}
		Double_t GetTankHeight() {return TankHeight_mng;}

		void PrintToScreen(G4String input) {G4cout << input << G4endl;}
	
		// initialise, increment and get counters
		void InitialiseElectronCounter() {ElectronCounter_mng = 0;}
		void IncrementElectronCounter() {ElectronCounter_mng++;}
		Int_t GetElectronCounter() {return ElectronCounter_mng;}
	
		void InitialiseSecondaryScintCounter() {SecondaryScintCounter_mng = 0;}
		void AddToSecondaryScintCounter(Int_t input) {SecondaryScintCounter_mng += input;}
		Int_t GetSecondaryScintCounter() {return SecondaryScintCounter_mng;}
	
		/*void SetInitialMomentum(Double_t input_pabs, Double_t input_px, Double_t input_py, Double_t input_pz)
											{InitialMomentum_mng[0] = input_pabs;
											 InitialMomentum_mng[1] = input_px;
											 InitialMomentum_mng[2] = input_py;
											 InitialMomentum_mng[3] = input_pz;}
		Double_t GetInitialMomentumTanPhi(){return InitialMomentum_mng[2]/InitialMomentum_mng[1];}
		Double_t GetInitialMomentumCosTheta(){return InitialMomentum_mng[3]/InitialMomentum_mng[0];}*/
	
		void SetTrueTheta(Double_t input){TrueTheta_mng = input;}
		void SetTruePhi(Double_t input){TruePhi_mng = input;}
	
		void FlagFirstStep(){IsFirstStep_mng = true;}
		void UnflagFirstStep(){IsFirstStep_mng = false;}
		Bool_t IsFirstStep(){return IsFirstStep_mng;}
	
		void SetElectricField(Double_t input){ElectricField_mng = input;}
		Double_t GetElectricField(){return ElectricField_mng;}
	
		Double_t GetElectronMobility(){return DriftVelocity_mng/ElectricField_mng;}
	
		void SetTemperature(Double_t input){Temperature_mng = input;}
		Double_t GetTemperature(){return Temperature_mng;}
	
		void SetGasPressure(Double_t input){GasPressure_mng = input;}
		Double_t GetGasPressure(){return GasPressure_mng;}
	
		// functions for camera settings
		Double_t GetLensRadius() {return LensRadius_mng;}
		Double_t GetLensCentreX() {return LensCentreX_mng;}
		Double_t GetLensCentreY() {return LensCentreY_mng;}
		Double_t GetScintToLensDistance() {return ScintToLensDistance_mng;}

		~DDMRootManager();
};

#endif

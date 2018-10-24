#include "TreeAccess.h"
#include <fstream>

TreeAccess::TreeAccess(std::string fileName, TTree *tree)
    :
    fChain(0),

    fIsCosmic(true),

    nf_TotalVisibleEnergy_cosmic(204.),
    nf_TotalHitCountInXView_cosmic(187.),
    nf_TotalHitCountInYView_cosmic(158.),
    nf_Prong3DCounter_cosmic(1.),
    nf_Prong2DCounter_cosmic(1.),
    nf_AverageEnergyPerHitXView_cosmic(612.),
    nf_AverageEnergyPerHitYView_cosmic(609.),
    nf_HitCountXYDifference_cosmic(287.),
    nf_MaximumProngEnergyLossPerLength_cosmic(1.),
    nf_MinimumProngEnergyLossPerLength_cosmic(1.),
    nf_AverageProngEnergyLossPerLength_cosmic(1.),
    nf_AreaRatioXV_cosmic(214.),
    nf_AreaRatioYV_cosmic(252.),
    nf_AverageYPosition_cosmic(100.),

    nf_TotalVisibleEnergy_signal(301.),
    nf_TotalHitCountInXView_signal(290.),
    nf_TotalHitCountInYView_signal(305.),
    nf_Prong3DCounter_signal(1),
    nf_Prong2DCounter_signal(1),
    nf_AverageEnergyPerHitXView_signal(404.),
    nf_AverageEnergyPerHitYView_signal(383.),
    nf_HitCountXYDifference_signal(293.),
    nf_MaximumProngEnergyLossPerLength_signal(1.),
    nf_MinimumProngEnergyLossPerLength_signal(1.),
    nf_AverageProngEnergyLossPerLength_signal(1.),
    nf_AreaRatioXV_signal(193.),
    nf_AreaRatioYV_signal(189.),
    nf_AverageYPosition_signal(100.),

    fVisECut(false),
    fAvgEPerHitYViewCut(false),
    fAvgEPerHitXViewCut(false),
    fProng3DCounterCut(false),
    fProng2DCounterCut(false),
    fAvgYPositionCut(false),
    fTotHitCountXViewCut(false),
    fTotHitCountYViewCut(false),
    fAreaRatioXViewCut(false),
    fAreaRatioYViewCut(false),
    fMaximumProngEnergyLossPerLengthCut(false),
    fMinimumProngEnergyLossPerLengthCut(false),
    fAverageProngEnergyLossPerLengthCut(false),
    fAvgEPerHitCompositeCut(false) {


  if (tree == 0) {
    TFile *f = (TFile *) gROOT->GetListOfFiles()->FindObject(fileName.c_str());
    if (!f || !f->IsOpen()) {
      f = new TFile(fileName.c_str());
    }
    std::string folderName = fileName + ":/cosmicshoweranalyzer";
    TDirectory *dir = (TDirectory *) f->Get(folderName.c_str());
    dir->GetObject("t_VariableTree", tree);

  }
  Init(tree);

  h_TotalVisibleEnergy = new TH1D("TotalVisibleEnergy", ";Visible Energy (GeV); Normalized Count", 150, 0, 3);
  h_TotalHitCountInXView = new TH1D("TotalHitCountInXView", ";Hit Count X-view; Normalized Count", 100, 0, 100);
  h_TotalHitCountInYView = new TH1D("TotalHitCountInYView", ";Hit Count Y-view; Normalized Count", 100, 0, 100);
  h_Prong3DCounter = new TH1D("Prong3DCounter", ";Number of 3D Prongs; Normalized Count", 10, 0, 10);
  h_Prong2DCounter = new TH1D("Prong2DCounter", ";Number of 2D Prongs; Normalized Count", 20, 0, 20);
  h_AverageEnergyPerHitXView = new TH1D("AverageEnergyPerHitXView",
                                        ";Avg. Energy per Hit X-view (GeV); Normalized Count", 100, 0, 0.06);
  h_AverageEnergyPerHitYView = new TH1D("AverageEnergyPerHitYView",
                                        ";Avg. Energy per Hit Y-view (GeV); Normalized Count", 100, 0, 0.06);
  h_HitCountXYDifference = new TH1D("HitCountXYDifference", ";X-Y Hit Count Diff.; Normalized Count", 100, -50, 50);
  h_MaximumProngEnergyLossPerLength = new TH1D("MaximumProngEnergyLossPerLength", ";Maximum Prong dE/dX (GeV/m); Normalized Count", 100, 0, 0.030);
  h_MinimumProngEnergyLossPerLength = new TH1D("MinimumProngEnergyLossPerLength", ";Minimum Prong dE/dX (GeV/m); Normalized Count", 100, 0, 0.010);
  h_AverageProngEnergyLossPerLength = new TH1D("AverageProngEnergyLossPerLength", ";Average Prong dE/dX (GeV/m); Normalized Count", 100, 0, 0.015);
  h_AreaRatioXV = new TH1D("AreaRatioXV", ";Area Ratio X-view; Normalized Count", 100, 0, 1);
  h_AreaRatioYV = new TH1D("AreaRatioYV", ";Area Ratio Y-view; Normalized Count", 100, 0, 1);
  h_AverageYPosition = new TH1D("AverageYPosition", ";Avg. Y (cm); Normalized Count", 100, -800, 800);

  TH1DMaps["TotalVisibleEnergy"] = h_TotalVisibleEnergy;
  TH1DMaps["TotalHitCountInXView"] = h_TotalHitCountInXView;
  TH1DMaps["TotalHitCountInYView"] = h_TotalHitCountInYView;
  TH1DMaps["Prong3DCounter"] = h_Prong3DCounter;
  TH1DMaps["Prong2DCounter"] = h_Prong2DCounter;
  TH1DMaps["AverageEnergyPerHitXView"] = h_AverageEnergyPerHitXView;
  TH1DMaps["AverageEnergyPerHitYView"] = h_AverageEnergyPerHitYView;
  TH1DMaps["HitCountXYDifference"] = h_HitCountXYDifference;
  TH1DMaps["MaximumProngEnergyLossPerLength"] = h_MaximumProngEnergyLossPerLength;
  TH1DMaps["MinimumProngEnergyLossPerLength"] = h_MinimumProngEnergyLossPerLength;
  TH1DMaps["AverageProngEnergyLossPerLength"] = h_AverageProngEnergyLossPerLength;
  TH1DMaps["AreaRatioXV"] = h_AreaRatioXV;
  TH1DMaps["AreaRatioYV"] = h_AreaRatioYV;
  TH1DMaps["AverageYPosition"] = h_AverageYPosition;
}

TreeAccess::~TreeAccess() {
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t TreeAccess::GetEntry(Long64_t entry) {
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t TreeAccess::LoadTree(Long64_t entry) {
// Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void TreeAccess::Init(TTree *tree) {
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
  fChain->SetBranchAddress("SubrunNumber", &SubrunNumber, &b_SubrunNumber);
  fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
  fChain->SetBranchAddress("SliceNumber", &SliceNumber, &b_SliceNumber);
  fChain->SetBranchAddress("Prong3DCounter", &Prong3DCounter, &b_Prong3DCounter);
  fChain->SetBranchAddress("Prong2DCounter", &Prong2DCounter, &b_Prong2DCounter);
  fChain->SetBranchAddress("TotalVisibleEnergy", &TotalVisibleEnergy, &b_TotalVisibleEnergy);
  fChain->SetBranchAddress("TotalHitCountInXView", &TotalHitCountInXView, &b_TotalHitCountInXView);
  fChain->SetBranchAddress("TotalHitCountInYView", &TotalHitCountInYView, &b_TotalHitCountInYView);
  fChain->SetBranchAddress("HitCountXYDifference", &HitCountXYDifference, &b_HitCountXYDifference);
  fChain->SetBranchAddress("TemporalClusterExpand", &TemporalClusterExpand, &b_TemporalClusterExpand);
  fChain->SetBranchAddress("AverageEnergyPerHitXView", &AverageEnergyPerHitXView, &b_AverageEnergyPerHitXView);
  fChain->SetBranchAddress("AverageEnergyPerHitYView", &AverageEnergyPerHitYView, &b_AverageEnergyPerHitYView);
  fChain->SetBranchAddress("CorrelationTCellXView", &CorrelationTCellXView, &b_CorrelationTCellXView);
  fChain->SetBranchAddress("CorrelationTPlaneXView", &CorrelationTPlaneXView, &b_CorrelationTPlaneXView);
  fChain->SetBranchAddress("CorrelationTCellYView", &CorrelationTCellYView, &b_CorrelationTCellYView);
  fChain->SetBranchAddress("CorrelationTPlaneYView", &CorrelationTPlaneYView, &b_CorrelationTPlaneYView);
  fChain->SetBranchAddress("MaximumProngEnergyLossPerLength", &MaximumProngEnergyLossPerLength, &b_MaximumProngEnergyLossPerLength);
  fChain->SetBranchAddress("MinimumProngEnergyLossPerLength", &MinimumProngEnergyLossPerLength, &b_MinimumProngEnergyLossPerLength);
  fChain->SetBranchAddress("AverageProngEnergyLossPerLength", &AverageProngEnergyLossPerLength, &b_AverageProngEnergyLossPerLength);
  fChain->SetBranchAddress("ConvexHullAreaXV", &ConvexHullAreaXV, &b_ConvexHullAreaXV);
  fChain->SetBranchAddress("ConvexHullAreaYV", &ConvexHullAreaYV, &b_ConvexHullAreaYV);
  fChain->SetBranchAddress("MinimalEnclosingCircleAreaXV", &MinimalEnclosingCircleAreaXV, &b_MinimalEnclosingCircleAreaXV);
  fChain->SetBranchAddress("MinimalEnclosingCircleAreaYV", &MinimalEnclosingCircleAreaYV, &b_MinimalEnclosingCircleAreaYV);
  fChain->SetBranchAddress("AverageYposition", &AverageYposition, &b_AverageYposition);
  Notify();
}

Bool_t TreeAccess::Notify() {
  return kTRUE;
}

void TreeAccess::Show(Long64_t entry) {
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t TreeAccess::Cut(Long64_t entry) {
  return 1;
}

void TreeAccess::Terminate(std::string histName) {
  delete TH1DMaps[histName.c_str()];
}

TH1D *TreeAccess::GetTH1DByName(std::string histName) {
  NFMaps_Signal["TotalVisibleEnergy"] = nf_TotalVisibleEnergy_signal;
  NFMaps_Signal["TotalHitCountInXView"] = nf_TotalHitCountInXView_signal;
  NFMaps_Signal["TotalHitCountInYView"] = nf_TotalHitCountInYView_signal;
  NFMaps_Signal["Prong3DCounter"] = nf_Prong3DCounter_signal;
  NFMaps_Signal["Prong3DCounter"] = nf_Prong2DCounter_signal;
  NFMaps_Signal["AverageEnergyPerHitXView"] = nf_AverageEnergyPerHitXView_signal;
  NFMaps_Signal["AverageEnergyPerHitYView"] = nf_AverageEnergyPerHitYView_signal;
  NFMaps_Signal["HitCountXYDifference"] = nf_HitCountXYDifference_signal;
  NFMaps_Signal["MaximumProngEnergyLossPerLength"] = nf_MaximumProngEnergyLossPerLength_signal;
  NFMaps_Signal["MinimumProngEnergyLossPerLength"] = nf_MinimumProngEnergyLossPerLength_signal;
  NFMaps_Signal["AverageProngEnergyLossPerLength"] = nf_AverageProngEnergyLossPerLength_signal;
  NFMaps_Signal["AreaRatioXV"] = nf_AreaRatioXV_signal;
  NFMaps_Signal["AreaRatioYV"] = nf_AreaRatioYV_signal;
  NFMaps_Signal["AverageYPosition"] = nf_AverageYPosition_signal;


  NFMaps_Cosmic["TotalVisibleEnergy"] = nf_TotalVisibleEnergy_cosmic;
  NFMaps_Cosmic["TotalHitCountInXView"] = nf_TotalHitCountInXView_cosmic;
  NFMaps_Cosmic["TotalHitCountInYView"] = nf_TotalHitCountInYView_cosmic;
  NFMaps_Cosmic["Prong3DCounter"] = nf_Prong3DCounter_cosmic;
  NFMaps_Cosmic["Prong3DCounter"] = nf_Prong2DCounter_cosmic;
  NFMaps_Cosmic["AverageEnergyPerHitXView"] = nf_AverageEnergyPerHitXView_cosmic;
  NFMaps_Cosmic["AverageEnergyPerHitYView"] = nf_AverageEnergyPerHitYView_cosmic;
  NFMaps_Cosmic["HitCountXYDifference"] = nf_HitCountXYDifference_cosmic;
  NFMaps_Signal["MaximumProngEnergyLossPerLength"] = nf_MaximumProngEnergyLossPerLength_cosmic;
  NFMaps_Signal["MinimumProngEnergyLossPerLength"] = nf_MinimumProngEnergyLossPerLength_cosmic;
  NFMaps_Signal["AverageProngEnergyLossPerLength"] = nf_AverageProngEnergyLossPerLength_cosmic;
  NFMaps_Cosmic["AreaRatioXV"] = nf_AreaRatioXV_cosmic;
  NFMaps_Cosmic["AreaRatioYV"] = nf_AreaRatioYV_cosmic;
  NFMaps_Cosmic["AverageYPosition"] = nf_AverageYPosition_cosmic;

  TH1D *hist = TH1DMaps[histName.c_str()];
  double normFactor = 0; // No normalization
  // double normFactor = fIsCosmic? NFMaps_Cosmic[histName.c_str()] : NFMaps_Signal[histName.c_str()]; // Normalize sample to the number of events
  Normalize(hist, normFactor);
  return hist;
}

void TreeAccess::Normalize(TH1D *hist, double normFactor) {
  double maxValue;
  if (normFactor == 0) {
    maxValue = hist->GetMaximum();
  } else {
    maxValue = normFactor;
  }
  for (unsigned int i = 0; i < hist->GetSize(); i++) {
    double currentValue = hist->GetBinContent(i);
    hist->SetBinContent(i, currentValue / maxValue);
  }
}

void TreeAccess::SetSignal() {
  fIsCosmic = false;
}

bool TreeAccess::PassVisECut() {
  return ((TotalVisibleEnergy >= fVisibleEnergyLowerLimit) && (TotalVisibleEnergy <= fVisibleEnergyUpperLimit));
}

bool TreeAccess::PassProng3DCounterCut() {
  return ((Prong3DCounter >= fProng3DCounterLowerLimit) && (Prong3DCounter <= fProng3DCounterUpperLimit));
}

bool TreeAccess::PassProng2DCounterCut() {
  return true;
}

bool TreeAccess::PassAvgEPerHitYViewCut() {
  return ((AverageEnergyPerHitYView >= fAvgEPerHitYViewLowerLimit) && (AverageEnergyPerHitYView <= fAvgEPerHitYViewUpperLimit));
}

bool TreeAccess::PassAvgEPerHitXViewCut() {
  return ((AverageEnergyPerHitXView >= fAvgEPerHitXViewLowerLimit) && (AverageEnergyPerHitXView <= fAvgEPerHitXViewUpperLimit));
}

bool TreeAccess::PassAvgYPositionCut() {
  return ((AverageYposition <= fAvgYPositionUpperLimit) && (AverageYposition >= fAvgYPositionLowerLimit));
}

bool TreeAccess::PassTotHitCountXViewCut() {
  return (TotalHitCountInXView <= fTotHitCountXViewUpperLimit) && (TotalHitCountInXView >= fTotHitCountXViewLowerLimit);
}

bool TreeAccess::PassTotHitCountYViewCut() {
  return (TotalHitCountInYView <= fTotHitCountYViewUpperLimit) && (TotalHitCountInYView >= fTotHitCountYViewLowerLimit);
}

bool TreeAccess::PassAreaRatioXViewCut() {
  return ((ConvexHullAreaXV / MinimalEnclosingCircleAreaXV) >= 0.05);
}

bool TreeAccess::PassAreaRatioYViewCut() {
  return ((ConvexHullAreaYV / MinimalEnclosingCircleAreaYV) >= 0.1);
}

bool TreeAccess::PassMaximumProngEnergyLossPerLengthCut() {
  return ((MaximumProngEnergyLossPerLength >= fMaximumProngEnergyLossPerLengthLowerLimit)
          && (MaximumProngEnergyLossPerLength <= fMaximumProngEnergyLossPerLengthUpperLimit));
}

bool TreeAccess::PassMinimumProngEnergyLossPerLengthCut() {
  return ((MinimumProngEnergyLossPerLength >= fMinimumProngEnergyLossPerLengthLowerLimit)
          && (MinimumProngEnergyLossPerLength <= fMinimumProngEnergyLossPerLengthUpperLimit));
}

bool TreeAccess::PassAverageProngEnergyLossPerLengthCut() {
  return (AverageProngEnergyLossPerLength >= 0);
}

bool TreeAccess::PassAvgEPerHitCompositeCut() {
  return PassAvgEPerHitYViewCut() && PassAvgEPerHitXViewCut();
}

void TreeAccess::SetEnergyCut(double lowerLim, double upperLim) {
  fVisibleEnergyLowerLimit = lowerLim;
  fVisibleEnergyUpperLimit = upperLim;
  fVisECut = true;
}

void TreeAccess::SetProng3DCounterCut(int lowerLim, int upperLim) {
  fProng3DCounterLowerLimit = lowerLim;
  fProng3DCounterUpperLimit = upperLim;
  fProng3DCounterCut = true;
}

void TreeAccess::SetProng2DCounterCut() {
  fProng2DCounterCut = true;
}

void TreeAccess::SetEnergyPerHitYViewCut(double lowerLim, double upperLim) {
  fAvgEPerHitYViewLowerLimit = lowerLim;
  fAvgEPerHitYViewUpperLimit = upperLim;
  fAvgEPerHitYViewCut = true;
}

void TreeAccess::SetEnergyPerHitXViewCut(double lowerLim, double upperLim) {
  fAvgEPerHitXViewLowerLimit = lowerLim;
  fAvgEPerHitXViewUpperLimit = upperLim;
  fAvgEPerHitXViewCut = true;
}

void TreeAccess::SetAverageYPositionCut(double lowerLim, double upperLim) {
  fAvgYPositionLowerLimit = lowerLim;
  fAvgYPositionUpperLimit = upperLim;
  fAvgYPositionCut = true;
}

void TreeAccess::SetTotHitCountXViewCut(int lowerLim, int upperLim) {
  fTotHitCountXViewLowerLimit = lowerLim;
  fTotHitCountXViewUpperLimit = upperLim;
  fTotHitCountXViewCut = true;
}

void TreeAccess::SetTotHitCountYViewCut(int lowerLim, int upperLim) {
  fTotHitCountYViewLowerLimit = lowerLim;
  fTotHitCountYViewUpperLimit = upperLim;
  fTotHitCountYViewCut = true;
}

void TreeAccess::SetAreaRatioXViewCut() {
  fAreaRatioXViewCut = true;
}

void TreeAccess::SetAreaRatioYViewCut() {
  fAreaRatioYViewCut = true;
}

void TreeAccess::SetAvgEPerHitCompositeCut() {
  fAvgEPerHitCompositeCut = true;
}

void TreeAccess::SetMaximumProngEnergyLossPerLengthCut(double lowerLim, double upperLim) {
  fMaximumProngEnergyLossPerLengthLowerLimit = lowerLim;
  fMaximumProngEnergyLossPerLengthUpperLimit = upperLim;
  fMaximumProngEnergyLossPerLengthCut = true;
}

void TreeAccess::SetMinimumProngEnergyLossPerLengthCut(double lowerLim, double upperLim) {
  fMinimumProngEnergyLossPerLengthLowerLimit = lowerLim;
  fMinimumProngEnergyLossPerLengthUpperLimit = upperLim;
  fMinimumProngEnergyLossPerLengthCut = true;
}

void TreeAccess::SetAverageProngEnergyLossPerLengthCut() {
  fAverageProngEnergyLossPerLengthCut = true;
}

void TreeAccess::Loop() {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  unsigned int survCount = 0;

  std::ofstream dataOut("data.dat");
  for (Long64_t jentry = 0; jentry < nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
//    dataOut << Form("%.5f, %.5f, %.5f, %.5f, %.5f, %d, %d, %.5f, %.5f, %.5f, %.5f, %.5f, %.5f, %.5f, %d \n",
//                    TotalVisibleEnergy,
//                    TotalHitCountInXView,
//                    TotalHitCountInYView,
//                    AverageEnergyPerHitXView,
//                    AverageEnergyPerHitYView,
//                    Prong2DCounter,
//                    Prong3DCounter,
//                    HitCountXYDifference,
//                    MaximumProngEnergyLossPerLength,
//                    MinimumProngEnergyLossPerLength,
//                    AverageProngEnergyLossPerLength,
//                    ConvexHullAreaXV / MinimalEnclosingCircleAreaXV,
//                    ConvexHullAreaYV / MinimalEnclosingCircleAreaYV,
//                    AverageYposition,
//                    0);

    // Apply cut here
    if (fVisECut && !PassVisECut()) continue;
    if (fAvgEPerHitXViewCut && !PassAvgEPerHitXViewCut()) continue;
    if (fAvgEPerHitYViewCut && !PassAvgEPerHitYViewCut()) continue;
    if (fProng3DCounterCut && !PassProng3DCounterCut()) continue;
    if (fProng2DCounterCut && !PassProng2DCounterCut()) continue;
    if (fAvgYPositionCut && !PassAvgYPositionCut()) continue;
    if (fTotHitCountXViewCut && !PassTotHitCountXViewCut()) continue;
    if (fTotHitCountYViewCut && !PassTotHitCountYViewCut()) continue;
    if (fAreaRatioXViewCut && !PassAreaRatioXViewCut()) continue;
    if (fAreaRatioYViewCut && !PassAreaRatioYViewCut()) continue;
    if (fMaximumProngEnergyLossPerLengthCut && !PassMaximumProngEnergyLossPerLengthCut()) continue;
    if (fMinimumProngEnergyLossPerLengthCut && !PassMinimumProngEnergyLossPerLengthCut()) continue;
    if (fAverageProngEnergyLossPerLengthCut && !PassAverageProngEnergyLossPerLengthCut()) continue;
    survCount++;

//    if (fIsCosmic) {
//      std::cout << "Run #" << RunNumber << ". Subrun #" << SubrunNumber << ". Event #" << EventNumber
//                << ". Slice #" << SliceNumber << "." << std::endl;
//    }

    h_TotalVisibleEnergy->Fill(TotalVisibleEnergy);
    h_TotalHitCountInXView->Fill(TotalHitCountInXView);
    h_TotalHitCountInYView->Fill(TotalHitCountInYView);
    h_AverageEnergyPerHitXView->Fill(AverageEnergyPerHitXView);
    h_AverageEnergyPerHitYView->Fill(AverageEnergyPerHitYView);
    h_Prong2DCounter->Fill(Prong2DCounter);
    h_Prong3DCounter->Fill(Prong3DCounter);
    h_HitCountXYDifference->Fill(HitCountXYDifference);
    h_MaximumProngEnergyLossPerLength->Fill(MaximumProngEnergyLossPerLength);
    h_MinimumProngEnergyLossPerLength->Fill(MinimumProngEnergyLossPerLength);
    h_AverageProngEnergyLossPerLength->Fill(AverageProngEnergyLossPerLength);
    h_AreaRatioXV->Fill(ConvexHullAreaXV / MinimalEnclosingCircleAreaXV);
    h_AreaRatioYV->Fill(ConvexHullAreaYV / MinimalEnclosingCircleAreaYV);
    h_AverageYPosition->Fill(AverageYposition);
  }
  dataOut.close();

  std::cout << "Survival slices: " << survCount << "." << std::endl;
}



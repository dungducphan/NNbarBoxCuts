#include "TreeAccess.h"

TreeAccess::TreeAccess(std::string fileName, TTree *tree)
:
  fChain(0),

  fIsCosmic(true),

  nf_TotalVisibleEnergy_cosmic(204.),
  nf_TotalHitCountInXView_cosmic(187.),
  nf_TotalHitCountInYView_cosmic(158.),
  nf_AverageEnergyPerHitXView_cosmic(612.),
  nf_AverageEnergyPerHitYView_cosmic(609.),
  nf_HitCountXYDifference_cosmic(287.),
  nf_AreaRatioXV_cosmic(214.),
  nf_AreaRatioYV_cosmic(252.),
  nf_AverageYPosition_cosmic(100.),

  nf_TotalVisibleEnergy_signal(301.),
  nf_TotalHitCountInXView_signal(290.),
  nf_TotalHitCountInYView_signal(305.),
  nf_AverageEnergyPerHitXView_signal(404.),
  nf_AverageEnergyPerHitYView_signal(383.),
  nf_HitCountXYDifference_signal(293.),
  nf_AreaRatioXV_signal(193.),
  nf_AreaRatioYV_signal(189.),
  nf_AverageYPosition_signal(100.),

  fVisECut(false),
  fAvgEPerHitYViewCut(false),
  fAvgEPerHitXViewCut(false),
  fAvgYPositionCut(false)
{


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
  h_AverageEnergyPerHitXView = new TH1D("AverageEnergyPerHitXView", ";Avg. Energy per Hit X-view (GeV); Normalized Count", 100, 0, 0.06);
  h_AverageEnergyPerHitYView = new TH1D("AverageEnergyPerHitYView", ";Avg. Energy per Hit Y-view (GeV); Normalized Count", 100, 0, 0.06);
  h_HitCountXYDifference = new TH1D("HitCountXYDifference", ";X-Y Hit Count Diff.; Normalized Count", 100, -50, 50);
  h_AreaRatioXV = new TH1D("AreaRatioXV", ";Area Ratio X-view; Normalized Count", 100, 0, 1);
  h_AreaRatioYV = new TH1D("AreaRatioYV", ";Area Ratio Y-view; Normalized Count", 100, 0, 1);
  h_AverageYPosition = new TH1D("AverageYPosition", ";Avg. Y (cm); Normalized Count", 100, -800, 800);

  TH1DMaps["TotalVisibleEnergy"] = h_TotalVisibleEnergy;
  TH1DMaps["TotalHitCountInXView"] = h_TotalHitCountInXView;
  TH1DMaps["TotalHitCountInYView"] = h_TotalHitCountInYView;
  TH1DMaps["AverageEnergyPerHitXView"] = h_AverageEnergyPerHitXView;
  TH1DMaps["AverageEnergyPerHitYView"] = h_AverageEnergyPerHitYView;
  TH1DMaps["HitCountXYDifference"] = h_HitCountXYDifference;
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
  fChain->SetBranchAddress("ConvexHullAreaXV", &ConvexHullAreaXV, &b_ConvexHullAreaXV);
  fChain->SetBranchAddress("ConvexHullAreaYV", &ConvexHullAreaYV, &b_ConvexHullAreaYV);
  fChain->SetBranchAddress("MinimalEnclosingCircleAreaXV", &MinimalEnclosingCircleAreaXV,
                           &b_MinimalEnclosingCircleAreaXV);
  fChain->SetBranchAddress("MinimalEnclosingCircleAreaYV", &MinimalEnclosingCircleAreaYV,
                           &b_MinimalEnclosingCircleAreaYV);
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

TH1D* TreeAccess::GetTH1DByName(std::string histName) {
  NFMaps_Signal["TotalVisibleEnergy"] = nf_TotalVisibleEnergy_signal;
  NFMaps_Signal["TotalHitCountInXView"] = nf_TotalHitCountInXView_signal;
  NFMaps_Signal["TotalHitCountInYView"] = nf_TotalHitCountInYView_signal;
  NFMaps_Signal["AverageEnergyPerHitXView"] = nf_AverageEnergyPerHitXView_signal;
  NFMaps_Signal["AverageEnergyPerHitYView"] = nf_AverageEnergyPerHitYView_signal;
  NFMaps_Signal["HitCountXYDifference"] = nf_HitCountXYDifference_signal;
  NFMaps_Signal["AreaRatioXV"] = nf_AreaRatioXV_signal;
  NFMaps_Signal["AreaRatioYV"] = nf_AreaRatioYV_signal;
  NFMaps_Signal["AverageYPosition"] = nf_AverageYPosition_signal;


  NFMaps_Cosmic["TotalVisibleEnergy"] = nf_TotalVisibleEnergy_cosmic;
  NFMaps_Cosmic["TotalHitCountInXView"] = nf_TotalHitCountInXView_cosmic;
  NFMaps_Cosmic["TotalHitCountInYView"] = nf_TotalHitCountInYView_cosmic;
  NFMaps_Cosmic["AverageEnergyPerHitXView"] = nf_AverageEnergyPerHitXView_cosmic;
  NFMaps_Cosmic["AverageEnergyPerHitYView"] = nf_AverageEnergyPerHitYView_cosmic;
  NFMaps_Cosmic["HitCountXYDifference"] = nf_HitCountXYDifference_cosmic;
  NFMaps_Cosmic["AreaRatioXV"] = nf_AreaRatioXV_cosmic;
  NFMaps_Cosmic["AreaRatioYV"] = nf_AreaRatioYV_cosmic;
  NFMaps_Cosmic["AverageYPosition"] = nf_AverageYPosition_cosmic;

  TH1D* hist = TH1DMaps[histName.c_str()];
  double normFactor = 0; // No normalization
  // double normFactor = fIsCosmic? NFMaps_Cosmic[histName.c_str()] : NFMaps_Signal[histName.c_str()]; // Normalize sample to the number of events
  Normalize(hist, normFactor);
  return hist;
}

void TreeAccess::Normalize(TH1D* hist, double normFactor) {
  double maxValue;
  if (normFactor == 0) {
    maxValue = hist->GetMaximum();
  } else {
    maxValue = normFactor;
  }
  for (unsigned int i = 0; i < hist->GetSize(); i++) {
    double currentValue = hist->GetBinContent(i);
    hist->SetBinContent(i, currentValue/maxValue);
  }
}

void TreeAccess::SetSignal() {
  fIsCosmic = false;
}

bool TreeAccess::PassVisECut() {
  return ((TotalVisibleEnergy >= 1) && (TotalVisibleEnergy <= 1.5));
}

bool TreeAccess::PassAvgEPerHitYViewCut() {
  return (AverageEnergyPerHitYView >= 0.02);
}

bool TreeAccess::PassAvgEPerHitXViewCut() {
  return (AverageEnergyPerHitXView >= 0.01);
}

bool TreeAccess::PassAvgYPositionCut() {
  return (AverageYposition <= 300);
}


void TreeAccess::SetEnergyCut() {
  fVisECut = true;
}

void TreeAccess::SetEnergyPerHitYViewCut() {
  fAvgEPerHitYViewCut = true;
}

void TreeAccess::SetEnergyPerHitXViewCut() {
  fAvgEPerHitXViewCut = true;
}

void TreeAccess::SetAverageYPositionCut() {
  fAvgYPositionCut = true;
}

void TreeAccess::Loop() {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  unsigned int survCount = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    // Apply cut here
    if (fVisECut && !PassVisECut()) continue;
    if (fAvgEPerHitYViewCut && !PassAvgEPerHitYViewCut()) continue;
    if (fAvgEPerHitXViewCut && !PassAvgEPerHitXViewCut()) continue;
    if (fAvgYPositionCut && !PassAvgYPositionCut()) continue;
    survCount++;

    h_TotalVisibleEnergy->Fill(TotalVisibleEnergy);
    h_TotalHitCountInXView->Fill(TotalHitCountInXView);
    h_TotalHitCountInYView->Fill(TotalHitCountInYView);
    h_AverageEnergyPerHitXView->Fill(AverageEnergyPerHitXView);
    h_AverageEnergyPerHitYView->Fill(AverageEnergyPerHitYView);
    h_HitCountXYDifference->Fill(HitCountXYDifference);
    h_AreaRatioXV->Fill(ConvexHullAreaXV/MinimalEnclosingCircleAreaXV);
    h_AreaRatioYV->Fill(ConvexHullAreaYV/MinimalEnclosingCircleAreaYV);
    h_AverageYPosition->Fill(AverageYposition);
  }

  std::cout << "Total number of slices: " << nentries << "." << std::endl;
  std::cout << "Survival slices: " << survCount << "." << std::endl;
  std::cout << "Survival percent: " << 100 * ((double)survCount / (double) nentries) << "%." << std::endl;
}







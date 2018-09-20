#ifndef TreeAccess_h
#define TreeAccess_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <cstring>
#include <iostream>
#include <vector>
#include <map>

class TreeAccess {
public :
  TreeAccess(std::string, TTree *tree = 0);
  virtual ~TreeAccess();

  virtual Int_t Cut(Long64_t entry);
  virtual Int_t GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void Init(TTree *tree);
  virtual void Loop();
  virtual Bool_t Notify();
  virtual void Show(Long64_t entry = -1);
  virtual void Terminate(std::string);
  virtual TH1D* GetTH1DByName(std::string);
  virtual void Normalize(TH1D*, double normFactor = 0.);
  virtual void SetSignal();
  virtual void SetEnergyCut();
  virtual void SetEnergyPerHitYViewCut();
  virtual void SetEnergyPerHitXViewCut();
  virtual void SetAverageYPositionCut();

private:
  virtual bool PassVisECut();
  virtual bool PassAvgEPerHitYViewCut();
  virtual bool PassAvgEPerHitXViewCut();
  virtual bool PassAvgYPositionCut();

  bool fVisECut;
  bool fAvgEPerHitYViewCut;
  bool fAvgEPerHitXViewCut;
  bool fAvgYPositionCut;

  bool fIsCosmic;

  TTree *fChain;
  Int_t fCurrent;

  Double_t TotalVisibleEnergy;
  Double_t TotalHitCountInXView;
  Double_t TotalHitCountInYView;
  Double_t HitCountXYDifference;
  Double_t TemporalClusterExpand;
  Double_t AverageEnergyPerHitXView;
  Double_t AverageEnergyPerHitYView;
  Double_t CorrelationTCellXView;
  Double_t CorrelationTPlaneXView;
  Double_t CorrelationTCellYView;
  Double_t CorrelationTPlaneYView;
  Double_t ConvexHullAreaXV;
  Double_t ConvexHullAreaYV;
  Double_t MinimalEnclosingCircleAreaXV;
  Double_t MinimalEnclosingCircleAreaYV;
  Double_t AverageYposition;

  TBranch *b_TotalVisibleEnergy;
  TBranch *b_TotalHitCountInXView;
  TBranch *b_TotalHitCountInYView;
  TBranch *b_HitCountXYDifference;
  TBranch *b_TemporalClusterExpand;
  TBranch *b_AverageEnergyPerHitXView;
  TBranch *b_AverageEnergyPerHitYView;
  TBranch *b_CorrelationTCellXView;
  TBranch *b_CorrelationTPlaneXView;
  TBranch *b_CorrelationTCellYView;
  TBranch *b_CorrelationTPlaneYView;
  TBranch *b_ConvexHullAreaXV;
  TBranch *b_ConvexHullAreaYV;
  TBranch *b_MinimalEnclosingCircleAreaXV;
  TBranch *b_MinimalEnclosingCircleAreaYV;
  TBranch *b_AverageYposition;

  TH1D* h_TotalVisibleEnergy;
  TH1D* h_TotalHitCountInXView;
  TH1D* h_TotalHitCountInYView;
  TH1D* h_AverageEnergyPerHitXView;
  TH1D* h_AverageEnergyPerHitYView;
  TH1D* h_HitCountXYDifference;
  TH1D* h_AreaRatioXV;
  TH1D* h_AreaRatioYV;
  TH1D* h_AverageYPosition;

  double nf_TotalVisibleEnergy_cosmic;
  double nf_TotalHitCountInXView_cosmic;
  double nf_TotalHitCountInYView_cosmic;
  double nf_AverageEnergyPerHitXView_cosmic;
  double nf_AverageEnergyPerHitYView_cosmic;
  double nf_HitCountXYDifference_cosmic;
  double nf_AreaRatioXV_cosmic;
  double nf_AreaRatioYV_cosmic;
  double nf_AverageYPosition_cosmic;

  double nf_TotalVisibleEnergy_signal;
  double nf_TotalHitCountInXView_signal;
  double nf_TotalHitCountInYView_signal;
  double nf_AverageEnergyPerHitXView_signal;
  double nf_AverageEnergyPerHitYView_signal;
  double nf_HitCountXYDifference_signal;
  double nf_AreaRatioXV_signal;
  double nf_AreaRatioYV_signal;
  double nf_AverageYPosition_signal;

  std::map<std::string, double> NFMaps_Cosmic;
  std::map<std::string, double> NFMaps_Signal;
  std::map<std::string, TH1D*> TH1DMaps;
};

#endif

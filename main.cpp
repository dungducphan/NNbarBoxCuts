#include <iostream>
#include "TreeAccess.h"
#include "Style.C"

#include <TLegend.h>

int main() {
  GeneralStyle();

  // Loading the data samples
  TreeAccess* cosmicTree = new TreeAccess("/Users/dphan/nova.nnbar.prongAnalyzer/OfflinePlotting/NNbar_Analysis_Hist.Cosmic.root");
  TreeAccess* signalTree = new TreeAccess("/Users/dphan/nova.nnbar.prongAnalyzer/OfflinePlotting/NNbar_Analysis_Hist.Signal.root");

  // Setting up the sample objects (always do this before Looping)
  signalTree->SetSignal();

  // Setting cuts
  cosmicTree->SetEnergyCut();
  signalTree->SetEnergyCut();
  cosmicTree->SetEnergyPerHitYViewCut();
  signalTree->SetEnergyPerHitYViewCut();
  cosmicTree->SetEnergyPerHitXViewCut();
  signalTree->SetEnergyPerHitXViewCut();
  cosmicTree->SetAverageYPositionCut();
  signalTree->SetAverageYPositionCut();


  // Looping
  cosmicTree->Loop();
  signalTree->Loop();

  std::vector<std::string> VarList; VarList.clear();
  VarList.push_back("TotalVisibleEnergy");
  VarList.push_back("TotalHitCountInXView");
  VarList.push_back("TotalHitCountInYView");
  VarList.push_back("AverageEnergyPerHitXView");
  VarList.push_back("AverageEnergyPerHitYView");
  VarList.push_back("HitCountXYDifference");
  VarList.push_back("AreaRatioXV");
  VarList.push_back("AreaRatioYV");
  VarList.push_back("AverageYPosition");

  for (unsigned int i = 0; i < VarList.size(); i++) {
    // Variables in question
    std::string VariableName = VarList.at(i);
    std::string AlternativeName_Cosmic = VariableName + "Cosmic";
    std::string AlternativeName_Signal = VariableName + "Signal";

    // Event Loop

    TH1D* hist2Plot_cosmic = (TH1D*) cosmicTree->GetTH1DByName(VariableName)->Clone(AlternativeName_Cosmic.c_str());
    cosmicTree->Terminate(VariableName.c_str());

    TH1D* hist2Plot_signal = (TH1D*) signalTree->GetTH1DByName(VariableName)->Clone(AlternativeName_Signal.c_str());
    signalTree->Terminate(VariableName.c_str());

    // Plotting
    auto c = new TCanvas("c", "c", 200, 200);
    StyleLinearLinear(c);
    hist2Plot_cosmic->GetYaxis()->SetRangeUser(0, 1.5);
    hist2Plot_cosmic->GetXaxis()->CenterTitle();
    hist2Plot_cosmic->GetYaxis()->CenterTitle();

    hist2Plot_cosmic->SetLineWidth(3);
    hist2Plot_signal->SetLineWidth(3);
    hist2Plot_signal->SetLineColor(kRed);

    hist2Plot_cosmic->Draw("HIST");
    hist2Plot_signal->Draw("HIST SAME");

    TLegend* leg = new TLegend(0.55, 0.7, 0.8, 0.85);
    leg->AddEntry(hist2Plot_cosmic, "Cosmic", "l");
    leg->AddEntry(hist2Plot_signal, "Signal", "l");
    leg->Draw();

    std::string plotFolder = "/Users/dphan/nova.nnbar.prongAnalyzer/OfflinePlotting/Plots";
    c->SetFixedAspectRatio();
    c->SaveAs(Form("%s/%s.AllCut.pdf", plotFolder.c_str(), VariableName.c_str()));
    delete c;
  }

  return 0;
}
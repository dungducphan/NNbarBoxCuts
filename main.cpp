#include <iostream>
#include "TreeAccess.h"
#include "Style.C"

#include <TLegend.h>

int main() {
    GeneralStyle();

    TreeAccess *cosmicTree = new TreeAccess("/home/dphan/nova.nnbar/composeCuts/NNbarBoxCuts/NNbar_Analysis_Hist.Cosmic.root");
    TreeAccess *signalTree = new TreeAccess("/home/dphan/nova.nnbar/composeCuts/NNbarBoxCuts/NNbar_Analysis_Hist.Signal.root");
    signalTree->SetSignal();

//    // Setting cuts
//    std::string cutLevel = "";
//
//    cosmicTree->SetAverageYPositionCut();
//    signalTree->SetAverageYPositionCut();
//    cutLevel += ".AvgYPos";
//
//    cosmicTree->SetEnergyCut();
//    signalTree->SetEnergyCut();
//    cutLevel += ".VisE";

//    cosmicTree->SetAvgEPerHitCompositeCut();
//    signalTree->SetAvgEPerHitCompositeCut();
//    cutLevel += ".AvgEHitComposite";

/*
    cosmicTree->SetEnergyPerHitYViewCut();
    signalTree->SetEnergyPerHitYViewCut();
    cutLevel += ".AvgEHitY";

    cosmicTree->SetEnergyPerHitXViewCut();
    signalTree->SetEnergyPerHitXViewCut();
    cutLevel += ".AvgEHitX";
*/

//    cosmicTree->SetTotHitCountXViewCut();
//    signalTree->SetTotHitCountXViewCut();
//    cutLevel += ".TotHitCountX";
//
//    cosmicTree->SetTotHitCountYViewCut();
//    signalTree->SetTotHitCountYViewCut();
//    cutLevel += ".TotHitCountY";
//
//    cosmicTree->SetAreaRatioXViewCut();
//    signalTree->SetAreaRatioXViewCut();
//    cutLevel += ".AreaRatioX";
//
//    cosmicTree->SetAreaRatioYViewCut();
//    signalTree->SetAreaRatioYViewCut();
//    cutLevel += ".AreaRatioY";

    // Looping
//    cosmicTree->Loop();
//    signalTree->Loop();

/*
    //------------------------------------------------------------------------------------------------------------------
    std::vector<std::string> VarList;
    VarList.clear();
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

        TH1D *hist2Plot_cosmic = (TH1D *) cosmicTree->GetTH1DByName(VariableName)->Clone(
                AlternativeName_Cosmic.c_str());
        cosmicTree->Terminate(VariableName.c_str());

        TH1D *hist2Plot_signal = (TH1D *) signalTree->GetTH1DByName(VariableName)->Clone(
                AlternativeName_Signal.c_str());
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

        TLegend *leg = new TLegend(0.55, 0.7, 0.8, 0.85);
        leg->AddEntry(hist2Plot_cosmic, "Cosmic", "l");
        leg->AddEntry(hist2Plot_signal, "Signal", "l");
        leg->Draw();

        std::string plotFolder = "/home/dphan/nova.nnbar/composeCuts/NNbarBoxCuts/Plots";
        c->SetFixedAspectRatio();
        c->SaveAs(Form("%s/%s%s.pdf", plotFolder.c_str(), VariableName.c_str(), cutLevel.c_str()));
        delete c;
    }
*/


    //------------------------------------------------------------------------------------------------------------------
//    std::vector<std::string> VarList2D;
//    VarList2D.clear();
//    VarList2D.push_back("AverageEnergyPerHit");
//    VarList2D.push_back("AreaRatio");
//    for (unsigned int i = 0; i < VarList2D.size(); i++) {
//        // Variables in question
//        std::string VariableName = VarList2D.at(i);
//        std::string AlternativeName_Cosmic = VariableName + "Cosmic";
//        std::string AlternativeName_Signal = VariableName + "Signal";

//        // Event Loop
//
//        TH2D *hist2Plot_cosmic = (TH2D*) cosmicTree->GetTH2DByName(VariableName)->Clone(AlternativeName_Cosmic.c_str());
//        hist2Plot_cosmic->SetTitle("Cosmic");
//        hist2Plot_cosmic->GetXaxis()->CenterTitle();
//        hist2Plot_cosmic->GetYaxis()->CenterTitle();
//        cosmicTree->Terminate2D(VariableName.c_str());
//
//        TH2D *hist2Plot_signal = (TH2D*) signalTree->GetTH2DByName(VariableName)->Clone(AlternativeName_Signal.c_str());
//        hist2Plot_signal->SetTitle("Signal");
//        hist2Plot_signal->GetXaxis()->CenterTitle();
//        hist2Plot_signal->GetYaxis()->CenterTitle();
//        signalTree->Terminate2D(VariableName.c_str());
//
//        // Plotting
//        auto c = new TCanvas("c", "c", 200, 400);
//        c->Divide(2, 1);
//
//        c->cd(1);
//        hist2Plot_cosmic->Draw("COLZ");
//        c->cd(2);
//        hist2Plot_signal->Draw("COLZ");
//
//        std::string plotFolder = "/home/dphan/nova.nnbar/composeCuts/NNbarBoxCuts/Plots";
//        c->SetFixedAspectRatio();
//        c->SaveAs(Form("%s/%s%s.pdf", plotFolder.c_str(), VariableName.c_str(), cutLevel.c_str()));
//        delete c;
//    }

    return 0;
}
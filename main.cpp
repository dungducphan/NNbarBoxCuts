#include <iostream>
#include "TreeAccess.h"
#include "Style.C"

#include <TLegend.h>
#include <TF1.h>

int main() {
    GeneralStyle();

    TreeAccess *cosmicTree = new TreeAccess(
            "../Cosmic.NNbar_Analysis_Hist.root");
    TreeAccess *signalTree = new TreeAccess(
            "../Signal.NNbar_Analysis_Hist.root");
    signalTree->SetSignal();

    // Setting cuts
    std::string cutLevel = "";

    cosmicTree->SetAverageYPositionCut();
    signalTree->SetAverageYPositionCut();
    cutLevel += "_AvgYPos";

    cosmicTree->SetEnergyCut();
    signalTree->SetEnergyCut();
    cutLevel += "_VisE";

    cosmicTree->SetEnergyPerHitYViewCut();
    signalTree->SetEnergyPerHitYViewCut();
    cutLevel += "_AvgEHitY";

    cosmicTree->SetEnergyPerHitXViewCut();
    signalTree->SetEnergyPerHitXViewCut();
    cutLevel += "_AvgEHitX";

    cosmicTree->SetAreaRatioYViewCut();
    signalTree->SetAreaRatioYViewCut();
    cutLevel += "_AreaRatioY";

//  cosmicTree->SetAreaRatioXViewCut();
//  signalTree->SetAreaRatioXViewCut();
//  cutLevel += ".AreaRatioX";

//  cosmicTree->SetTotHitCountXViewCut();
//  signalTree->SetTotHitCountXViewCut();
//  cutLevel += ".TotHitCountX";

//  cosmicTree->SetTotHitCountYViewCut();
//  signalTree->SetTotHitCountYViewCut();
//  cutLevel += ".TotHitCountY";

    cosmicTree->Loop();
    signalTree->Loop();

    //------------------------------------------------------------------------------------------------------------------
    std::vector<std::string> VarList;
    VarList.clear();
    VarList.push_back("TotalVisibleEnergy");
    VarList.push_back("TotalHitCountInXView");
    VarList.push_back("TotalHitCountInYView");
    VarList.push_back("Prong3DCounter");
    VarList.push_back("Prong2DCounter");
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
        TH1D *hist2Plot_cosmic = (TH1D *) cosmicTree->GetTH1DByName(VariableName)->Clone(AlternativeName_Cosmic.c_str());
        cosmicTree->Terminate(VariableName.c_str());

        TH1D *hist2Plot_signal = (TH1D *) signalTree->GetTH1DByName(VariableName)->Clone(AlternativeName_Signal.c_str());
        signalTree->Terminate(VariableName.c_str());

        TLine *line_A = new TLine(200, 0, 200, 1.5);
        TLine *line_B = new TLine(1.5, 0, 1.5, 1.5);
        line_A->SetLineColor(kBlue);
        line_A->SetLineStyle(kDashed);
        line_A->SetLineWidth(3);
        line_B->SetLineColor(kBlue);
        line_B->SetLineStyle(kDashed);
        line_B->SetLineWidth(3);

        // Plotting
        auto c = new TCanvas("c", "c", 200, 200);
        c->SetBatch(kTRUE);
        StyleLinearLinear(c);
        hist2Plot_cosmic->GetYaxis()->SetRangeUser(0, 1.5);
        hist2Plot_cosmic->GetXaxis()->CenterTitle();
        hist2Plot_cosmic->GetYaxis()->CenterTitle();

        hist2Plot_cosmic->SetLineWidth(3);
        hist2Plot_signal->SetLineWidth(3);
        hist2Plot_signal->SetLineColor(kRed);

        hist2Plot_cosmic->Draw("HIST");
        hist2Plot_signal->Draw("HIST SAME");
//    line_A->Draw();
//    line_B->Draw();

        TLegend *leg = new TLegend(0.55, 0.7, 0.8, 0.85);
        leg->AddEntry(hist2Plot_cosmic, "Cosmic", "l");
        leg->AddEntry(hist2Plot_signal, "Signal", "l");
        leg->Draw();

        std::string plotFolder = "../Plots";
        c->SetFixedAspectRatio();
        c->SaveAs(Form("%s/%s%s.pdf", plotFolder.c_str(), VariableName.c_str(), cutLevel.c_str()));
        delete c;
    }

    return 0;
}
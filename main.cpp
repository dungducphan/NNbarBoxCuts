#include <iostream>
#include <fstream>
#include <string>

#include "TreeAccess.h"
#include "Style.C"

#include <json.h>

#include <TLegend.h>
#include <TF1.h>

int main(int argc, char* argv[]) {
  GeneralStyle();

  std::string fileName;
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " -f <Config File>" << std::endl;
    return 1;
  } else {
    fileName = argv[2];
  }

  Json::Value root;
  std::ifstream configFile(Form("%s", fileName.c_str()), std::ifstream::binary);
  configFile >> root;

  int signal_decay_channel      = root.get("signal_decay_channel", "0").asInt();

  bool set_visible_energy_cut   = root.get("set_visible_energy_cut",   "false").asBool();
  bool set_avg_hit_energy_x_cut = root.get("set_avg_hit_energy_x_cut", "false").asBool();
  bool set_avg_hit_energy_y_cut = root.get("set_avg_hit_energy_y_cut", "false").asBool();
  bool set_tot_hit_count_x_cut  = root.get("set_tot_hit_count_x_cut",  "false").asBool();
  bool set_tot_hit_count_y_cut  = root.get("set_tot_hit_count_y_cut",  "false").asBool();
  bool set_avg_y_pos_cut        = root.get("set_avg_y_pos_cut",        "false").asBool();
  bool set_prong3d_count_cut    = root.get("set_prong3d_count_cut",    "false").asBool();
  bool set_max_prong_dedx_cut   = root.get("set_max_prong_dedx_cut",   "false").asBool();
  bool set_min_prong_dedx_cut   = root.get("set_min_prong_dedx_cut",   "false").asBool();

  int prong3d_count_lower       = root.get("prong3d_count_lower", "0").asInt();
  int prong3d_count_upper       = root.get("prong3d_count_upper", "20").asInt();

  int tot_hit_count_x_lower     = root.get("tot_hit_count_x_lower", "-1E30").asInt();
  int tot_hit_count_x_upper     = root.get("tot_hit_count_x_upper", "+1E30").asInt();
  int tot_hit_count_y_lower     = root.get("tot_hit_count_y_lower", "-1E30").asInt();
  int tot_hit_count_y_upper     = root.get("tot_hit_count_y_upper", "+1E30").asInt();

  double visible_energy_lower   = root.get("visible_energy_lower", "1").asDouble();
  double visible_energy_upper   = root.get("visible_energy_upper", "1.5").asDouble();

  double avg_hit_energy_x_lower = root.get("avg_hit_energy_x_lower", "0.015").asDouble();
  double avg_hit_energy_y_lower = root.get("avg_hit_energy_y_lower", "0.015").asDouble();
  double avg_hit_energy_x_upper = root.get("avg_hit_energy_x_upper", "+1E30").asDouble();
  double avg_hit_energy_y_upper = root.get("avg_hit_energy_y_upper", "+1E30").asDouble();

  double avg_y_pos_lower        = root.get("avg_y_pos_lower", "-1E10").asDouble();
  double avg_y_pos_upper        = root.get("avg_y_pos_upper", "200").asDouble();

  double max_prong_dedx_lower   = root.get("max_prong_dedx_lower", "0").asDouble();
  double max_prong_dedx_upper   = root.get("max_prong_dedx_upper", "1E30").asDouble();
  double min_prong_dedx_lower   = root.get("min_prong_dedx_lower", "0").asDouble();
  double min_prong_dedx_upper   = root.get("min_prong_dedx_upper", "1E30").asDouble();

  TreeAccess *cosmicTree = new TreeAccess("../Data/Cosmic.root");
  TreeAccess *signalTree = new TreeAccess(Form("../Data/Signal.Ch%i.root", signal_decay_channel));
  signalTree->SetSignal();

  // Setting cuts
  std::string cutLevel = "";

  if (set_visible_energy_cut) {
    cosmicTree->SetEnergyCut(visible_energy_lower, visible_energy_upper);
    signalTree->SetEnergyCut(visible_energy_lower, visible_energy_upper);
    cutLevel += "_VisE";
  }

  if (set_tot_hit_count_y_cut) {
    cosmicTree->SetTotHitCountYViewCut(tot_hit_count_y_lower, tot_hit_count_y_upper);
    signalTree->SetTotHitCountYViewCut(tot_hit_count_y_lower, tot_hit_count_y_upper);
    cutLevel += "_TotHitCountY";
  }

  if (set_tot_hit_count_x_cut) {
    cosmicTree->SetTotHitCountXViewCut(tot_hit_count_x_lower, tot_hit_count_x_upper);
    signalTree->SetTotHitCountXViewCut(tot_hit_count_x_lower, tot_hit_count_x_upper);
    cutLevel += "_TotHitCountX";
  }

  if (set_avg_hit_energy_y_cut) {
    cosmicTree->SetEnergyPerHitYViewCut(avg_hit_energy_y_lower, avg_hit_energy_y_upper);
    signalTree->SetEnergyPerHitYViewCut(avg_hit_energy_y_lower, avg_hit_energy_y_upper);
    cutLevel += "_AvgEHitY";
  }

  if (set_avg_hit_energy_x_cut) {
    cosmicTree->SetEnergyPerHitXViewCut(avg_hit_energy_x_lower, avg_hit_energy_x_upper);
    signalTree->SetEnergyPerHitXViewCut(avg_hit_energy_x_lower, avg_hit_energy_x_upper);
    cutLevel += "_AvgEHitX";
  }

  if (set_avg_y_pos_cut) {
    cosmicTree->SetAverageYPositionCut(avg_y_pos_lower, avg_y_pos_upper);
    signalTree->SetAverageYPositionCut(avg_y_pos_lower, avg_y_pos_upper);
    cutLevel += "_AvgYPos";
  }

  if (set_prong3d_count_cut) {
    cosmicTree->SetProng3DCounterCut(prong3d_count_lower, prong3d_count_upper);
    signalTree->SetProng3DCounterCut(prong3d_count_lower, prong3d_count_upper);
    cutLevel += "_Prong3D";
  }

  if (set_max_prong_dedx_cut) {
    cosmicTree->SetMaximumProngEnergyLossPerLengthCut(max_prong_dedx_lower, max_prong_dedx_upper);
    signalTree->SetMaximumProngEnergyLossPerLengthCut(max_prong_dedx_lower, max_prong_dedx_upper);
    cutLevel += "_MaximumProngELoss";
  }

  if (set_min_prong_dedx_cut) {
    cosmicTree->SetMinimumProngEnergyLossPerLengthCut(min_prong_dedx_lower, min_prong_dedx_upper);
    signalTree->SetMinimumProngEnergyLossPerLengthCut(min_prong_dedx_lower, min_prong_dedx_upper);
    cutLevel += "_MinimumProngELoss";
  }

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
  VarList.push_back("MaximumProngEnergyLossPerLength");
  VarList.push_back("MinimumProngEnergyLossPerLength");
  VarList.push_back("AverageProngEnergyLossPerLength");
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

    std::string plotFolder = Form("../Plots/Channel_%i", signal_decay_channel);
    c->SetFixedAspectRatio();
    c->SaveAs(Form("%s/%s%s.pdf", plotFolder.c_str(), VariableName.c_str(), cutLevel.c_str()));
    delete c;
  }

  return 0;
}
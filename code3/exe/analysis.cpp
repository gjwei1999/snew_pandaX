/*****************************/
/*                                                      */
/*       Created by Jiawei Guo          */
/*        Shandong University            */
/*                                                      */
/*****************************/

#include "TFile.h"

#include "branches.hpp"
#include "histogram.hpp"

int main(int argc, char* argv[]){
    
    //to run the code
    // ./analysis input_file

    if(argc != 3){
        std::cout<<"Error. The input parameters are wrong."<<std::endl;
        std::cout<<"Usage: "<<argv[0]<<" input_root_file   output_root_file_name"<<std::endl;
    }
    
    TString path1 = "/Users/jiaweiguo/Documents/GitHub/PandaX-4T_sdu/code3/output/";
    TString result_root = path1 + argv[2];
    
    TFile *fs1 = new TFile(result_root.Data(), "RECREATE");
    
    std::string input = argv[1];
    TFile *fs = new TFile(input.c_str(), "r");//input data
    TTree *t1 = (TTree*)fs->Get("qmc_tree");
    
    int num_of_events;
    num_of_events = (int)t1->GetEntries();

    
    Branches * branch1 = new Branches();
    branch1->init(t1);
    
    Histogram * histogram1 = new Histogram();
    
    t1->GetEntry(0);
    histogram1->Set_event_time(branch1->get_total_time());
    histogram1->Set_detected_event_time(branch1->get_total_time());
    
    int n_s1d = 0;
    int n_s2d = 0;
    int n_s1d_s2d = 0;
    
    for (int current_event = 0; current_event < num_of_events; current_event++) {
        
        // Get current event
        t1->GetEntry(current_event);
        
        
        if(branch1->get_S1d() > 0.0){
            n_s1d++;
        }
        
        if(branch1->get_S2d() > 0.0){
            n_s2d++;
        }
        
        if( (branch1->get_S2d() > 0.0) && (branch1->get_S2d() > 0.0)){
            n_s1d_s2d++;
        }
        
        histogram1->Fill_event_time(branch1);
        histogram1->Fill_detected_event_time(branch1);
        histogram1->Fill_logs2s1_s1(branch1);
        
        //std::cout<<"current event energy is "<<branch1->get_nQuanta()<<std::endl;
        
        
    }
    
    histogram1->Write(fs1);
    fs1->Write();
    
    std::cout<<"input "<< num_of_events <<" events "<<std::endl;
    std::cout<<"detected "<< n_s1d <<" S1 signal "<<std::endl;
    std::cout<<"detected "<< n_s2d <<" S2 signal "<<std::endl;
    std::cout<<"detected "<< n_s1d_s2d <<" S1 S2 signal "<<std::endl;
    
    return 1;
}

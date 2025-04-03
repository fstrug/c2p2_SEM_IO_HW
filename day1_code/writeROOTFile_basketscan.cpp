#include <vector>
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TBenchmark.h"
#include "TRandom.h"
#include "TSystem.h"


void write(Int_t basket_size, int N=1e6, int autoflush=-30000000, int vecsize=100) // that is the default autoflush value 
{
   TFile *f = TFile::Open(Form("hvector_%d_%d_%d.root",N,autoflush,vecsize), "RECREATE");
   float percentComplete = 0.0f; 
   if (!f) { return; }
   std::cout << "Basket_size: " << basket_size << std::endl;
   std::vector<float> vpx;
   std::vector<float> vpy;
   std::vector<float> vpz;
   std::vector<float> vpt;   
   std::vector<int> vint;

   
   // Create a TTree
   TTree *t = new TTree("tvec","Tree with vectors");
   
   t->SetAutoFlush(0);
   t->Branch("vpx",&vpx);
   t->Branch("vpy",&vpy);
   t->Branch("vpz",&vpz);   
   t->Branch("vpt",&vpt);
   t->Branch("vint",&vint); 
   int basketSizeBytes = basket_size*1024;
   t->SetBasketSize("*", basketSizeBytes );  
 
   gRandom->SetSeed();
   for (Int_t i = 0; i < N; i++) {

      // Monitor Progress
      if(i%10000==0) {
	   percentComplete =((float)i/N)*100.f;
      	   std::cerr << "\rLOOP [write()]: " << percentComplete << "\% Complete" <<  std::flush;
      }


      Int_t npx = (Int_t)(gRandom->Rndm(1)*vecsize);
 
      vpx.clear();
      vpy.clear();
      vpz.clear();
      vpt.clear();
      vint.clear();            
 
      for (Int_t j = 0; j < npx; ++j) {
 
         Float_t px,py,pz,pt;
         Int_t integer;
         gRandom->Rannor(px,py);
         pt = sqrt(px*px + py*py);
         pz = gRandom->Rndm(1);
         integer = (int)(gRandom->Rndm(1)*npx + npx);
 
         vpx.emplace_back(px);
         vpy.emplace_back(py);
         vpz.emplace_back(pz);
         
         /// this gets pushed back twice on purpose
         vpt.emplace_back(pt);
         vpt.emplace_back(pt);         
         vint.emplace_back(integer);         
 
      }
      t->Fill();
   }
   
   t->Print();
   f->Write();
   
   delete f;
}

 
 
 
// int main()
// {
//    int N = 1e6; // match this with N in readROOTFile.cpp
//    int vecsize=50;
//    std::vector<int> flushes;
//    flushes.emplace_back(0);
//    flushes.emplace_back(-30000000);
//    flushes.emplace_back(-1000000);
//    flushes.emplace_back(1e4);
//    flushes.emplace_back(1e2);   
//    const char* form;
//    // Timed write()
//    for (auto flush : flushes) {
//       std::cerr << "Flush = " << flush << " and N = " << N << " and vec size = " << vecsize << std::endl;
//       gBenchmark = new TBenchmark();
//       form =  Form("wr_hvec_N%d_F%d_Sz%d",N,flush,vecsize);
//       gBenchmark->Start(form);
//       write(N, flush); 
//       std::cout << std::endl; 
//       gBenchmark->Stop(form);
//       float rt, cp;
//       gBenchmark->Summary(rt, cp);
//       std::cout << "RT: " << rt << std::endl;
//       std::cout << "CP: " << cp << std::endl;
//       delete gBenchmark;
//    }

//    return 0;
// }

int main(){
   int N = 1e5; // match this with N in readROOTFile.cpp
   int vecsize=100;

   const char* form;
   // Timed write()
   Int_t basket_sizes[10] = {4, 8, 16, 32, 64, 128, 256, 512, 1024, 16000};
   for (Int_t i = 0; i < 12; i++){

      std::cerr << "N = " << N << " and vec size = " << vecsize << std::endl;
      gBenchmark = new TBenchmark();
      form =  Form("wr_hvec_N%d_Sz%d_basketsize_%d",N,vecsize, basket_sizes[i]);
      gBenchmark->Start(form);
      std::cout << "Basket size: " << basket_sizes[i] << std::endl;
      write(basket_sizes[i], N = N); 
      std::cout << std::endl; 
      gBenchmark->Stop(form);
      float rt, cp;
      gBenchmark->Summary(rt, cp);
      // std::cout << "RT: " << rt << std::endl;
      // std::cout << "CP: " << cp << std::endl;
      delete gBenchmark;
   }
   return 0;
}

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <cmath>
#include <getopt.h>
#include <sstream>
#include <cstdlib>
using namespace std;

int main(int argc, char **argv) {
  double factor = 0.995; 
  std::string factorfile ="CPUratio.txt";
  std::ifstream CPUtimeFile(factorfile.c_str(),std::ifstream::in);

  double realtime=0;
  double cputime=0;

  if ( CPUtimeFile ) {
    while ( !CPUtimeFile.eof() ) {
      CPUtimeFile >> realtime >> cputime ;
	}
	}
	if(realtime!=0 && cputime !=0 && cputime/realtime>0 && cputime/realtime<=1){
	factor=cputime/realtime;
	}

  std::string file = "TimingInfo.txt";
  int opt;
  std::string oval="";
  while ((opt = getopt(argc, argv, "on:t:")) != -1) {
    switch (opt) {
    case 'n':
      file=std::string(optarg);
      break;
    case 't':
      {
	std::istringstream fraction(optarg);      
	fraction >> factor; 
	factor*=0.01;
	break	 ;
      }
    case 'o':
      oval="[OVAL]" ;
      break;
    default: 
      fprintf(stderr, "Usage: %s -t [fraction of CPU in percentage] [-n filename TimingInfo.txt] [-o for oval] \n",
	      argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  std::cout << " Analyzing time report from " << file << " with CPU fraction correction " << factor << std::endl;

  std::map<std::string,double> timingPerModule, timingPerLabel;
  std::map<unsigned,double> timingPerEvent;
  std::ifstream myTimingFile(file.c_str(),std::ifstream::in);
  std::string dummy1, label, module;
  double timing;
  unsigned idummy1,evt;

  unsigned evt_temp=0;
  unsigned nevt=0;

  if ( myTimingFile ) {
    while ( !myTimingFile.eof() ) { 
      myTimingFile >> dummy1 >> evt >> idummy1 >> label >> module >> timing ;
      if(evt!=evt_temp){
        nevt++;
 	evt_temp=evt;
       }
       timingPerEvent[evt] += timing * factor * 1000.;	
       timingPerModule[module] += timing * factor * 1000.;
       timingPerLabel[module+":"+label] += timing * factor * 1000.;
    }
  } else {
    std::cout << "File " << file << " does not exist!" << std::endl;
  }

  std::map<std::string,double>::const_iterator modIt = timingPerModule.begin();
  std::map<std::string,double>::const_iterator labIt = timingPerLabel.begin();
  std::map<std::string,double>::const_iterator modEnd = timingPerModule.end();
  std::map<std::string,double>::const_iterator labEnd = timingPerLabel.end();
  std::map<double,std::string> modulePerTiming;
  std::map<double,std::string> labelPerTiming;

  for ( ; modIt != modEnd; ++modIt ) {
    double time = modIt->second/((double)nevt);
    std::string name = modIt->first;
    modulePerTiming[time] = name;
  }
    
  for ( ; labIt != labEnd; ++labIt ) {
    double time = labIt->second/((double)nevt);
    std::string name = labIt->first;
    labelPerTiming[time] = name;
  }
    
  std::map<double,std::string>::const_reverse_iterator timeIt = modulePerTiming.rbegin();
  std::map<double,std::string>::const_reverse_iterator timeEnd = modulePerTiming.rend();
  std::map<double,std::string>::const_reverse_iterator timeIt2 = labelPerTiming.rbegin();
  std::map<double,std::string>::const_reverse_iterator timeEnd2 = labelPerTiming.rend();


  double totalTimePre = 0.;

	for ( ; timeIt != timeEnd; ++timeIt ){
		    totalTimePre += timeIt->first;	
	}

	timeIt = modulePerTiming.rbegin();
	

  std::cout << "Timing per module " << std::endl;
  std::cout << "================= " << std::endl;
  double totalTime = 0.;
  unsigned i=1;
  for ( ; timeIt != timeEnd; ++timeIt ) {

    totalTime += timeIt->first;
    std::cout << oval << " " << std::setw(3) << i++ 
	      << std::setw(60) << timeIt->second << " : " 
	      << std::setw(9) << std::setprecision(3) << timeIt-> first << " ms/event"
				<< std::setw(10) << timeIt-> first/totalTimePre*100 << " \% "
	      << std::endl;
  }
  std::cout << "Total time = " << totalTime/1000. << " s/event " << std::endl;

  std::cout << "================= " << std::endl;
  std::cout << "Timing per label  " << std::endl;
  std::cout << "================= " << std::endl;
  totalTime = 0.;
  i = 1;
  for ( ; timeIt2 != timeEnd2; ++timeIt2 ) {

    totalTime += timeIt2->first;
    std::cout << oval << " " << std::setw(3) << i++ 
	      << std::setw(100) << timeIt2->second << " : " 
	      << std::setw(9) << std::setprecision(3) << timeIt2-> first << " ms/event"
				<< std::setw(10) << timeIt2-> first/totalTimePre*100 << " \% "
	      << std::endl;
  }
  std::cout << "================= " << std::endl;
  std::cout << "Total time = " << totalTime/1000. << " s/event " << std::endl;

  std::map<unsigned,double>::const_iterator eventIt = timingPerEvent.begin();
  std::map<unsigned,double>::const_iterator eventEnd = timingPerEvent.end();
  double minEv = 9999.;
  double maxEv = 0.;
  double rms = 0.;
  double mean = 0.;
  
  unsigned maxEvIndex=0;
  unsigned minEvIndex=0;

  for ( ; eventIt != eventEnd; ++eventIt ) { 
    //if ( eventIt->first == 1 ) continue;
    double timeEv = eventIt->second;
    if ( eventIt->second > maxEv ){ maxEv = timeEv;maxEvIndex =  eventIt->first ;}
    if ( eventIt->second < minEv ){ minEv = timeEv;minEvIndex =  eventIt->first ;}
    mean += timeEv;
    rms += timeEv*timeEv;    
  }

  mean /= (double)nevt;
  rms /= (double)nevt;
  rms = std::sqrt(rms-mean*mean);
  std::cout << "Total time = " << mean/1000. << " +/- " << rms/1000. << " s/event" << std::endl;
  std::cout << "Min.  time = " << minEv/1000. << " s/event" << std::endl;
  std::cout << "Max.  time = " << maxEv/1000. << " s/event" << std::endl;
  cout << "number of events" << nevt << endl;
}

/*
 * LDTest_test.cpp
 *
 *  Created on: Sep 17, 2014
 *      Author: ada
 */

#include "LDTest.h"
#include <boost/test/minimal.hpp>
#include <boost/random/discrete_distribution.hpp>
#include <boost/assert.hpp>
#include <boost/random/mersenne_twister.hpp>
boost::mt19937 boost_rng;

boost::shared_ptr<SHEsis::SHEsisData> GenerateRandomData(int sampleNum, int snpNum, int chrSetNum){
	double probabilities[]={0,0.48,0.48};//0.04 missing phenotype for individuals
	double probabilities2[]={0,0.5,0.5};//0.01 is missing genotype for individuals
	boost::random::discrete_distribution<> dist(probabilities);
	boost::random::discrete_distribution<> dist2(probabilities2);
	boost::shared_ptr<SHEsis::SHEsisData> data( new SHEsis::SHEsisData(sampleNum,snpNum,chrSetNum));
	for(int iSample=0;iSample<sampleNum;iSample++){
		BOOST_ASSERT(iSample<data->vLabel.size());
		data->vLabel[iSample]=((SHEsis::SampleStatus)dist(boost_rng));
		for(int iSnp=0;iSnp<snpNum;iSnp++){
			for(int iChrset=0;iChrset<chrSetNum;iChrset++){
				data->mGenotype[iSample][iSnp][iChrset]=dist2(boost_rng);
			}
		}
	}
//	BOOST_CHECK(sampleNum==data->mGenotype.shape()[0]);
//	BOOST_CHECK(snpNum==data->mGenotype.shape()[1]);
//	BOOST_CHECK(chrSetNum==data->mGenotype.shape()[2]);
	return data;
};
int
test_main(int,char*[]){
	int sampleNum=100;
	int chrSetNum=3;
	int snpNum=4;
	boost::shared_ptr<SHEsis::SHEsisData> data=GenerateRandomData(sampleNum,snpNum,chrSetNum);//(new SHEsis::SHEsisData(sampleNum,snpNum,chrSetNum));
//
//	int a[5][3][2]=
//	{{{2,1},{3,2},{2,2}},
//	{{1,1},{3,3},{4,2}},
//	{{1,1},{2,3},{4,2}},
//	{{2,1},{3,2},{4,4}},
//	{{2,2},{2,2},{2,2}}};
//
//		//34,32,24,22
//	for(int iSample=0;iSample<sampleNum;iSample++){
//		BOOST_ASSERT(iSample<data->vLabel.size());
//		data->vLabel[iSample]=iSample%2==0?SHEsis::CASE:SHEsis::CONTROL;
//		for(int iSnp=0;iSnp<snpNum;iSnp++){
//			for(int iChrset=0;iChrset<chrSetNum;iChrset++){
//				data->mGenotype[iSample][iSnp][iChrset]=a[iSample][iSnp][iChrset];
//			}
//		}
//	}


	std::stringstream ss;
	ss<<"snpnum_"<<snpNum<<".bmp";
	SHEsis::LDTest ld(data,ss.str());
	//ld.setForceSAT(true);
	ld.AllLociLDtest();
	ld.printRes();
	ld.DrawLDMap();
	return boost::exit_success;
}

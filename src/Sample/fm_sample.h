#ifndef FM_SAMPLE_H_
#define FM_SAMPLE_H_

#include <string>
#include <vector>
#include <exception>
#include <map>
using namespace std;

const string spliter = " ";
const string innerSpliter = ":";


class fm_sample
{
public:
    int y;
    vector<pair<string, double> > x;
    bool filter_flag;
    fm_sample(const string& line);
};


fm_sample::fm_sample(const string& line,vector<vector<string>> combineFeatures)
{
	try
	{
		this->filter_flag=false;
		this->x.clear();
		size_t posb = line.find_first_not_of(spliter, 0);
		size_t pose = line.find_first_of(spliter, posb);
		int label = atoi(line.substr(posb, pose-posb).c_str());
		this->y = label > 0 ? 1 : -1;
		string key;
		double value;
		map<string, string> map_feature;
		while(pose < line.size())
		{
			posb = line.find_first_not_of(spliter, pose);
			if(posb == string::npos)
			{
				break;
			}
			pose = line.find_first_of(innerSpliter, posb);
			if(pose == string::npos)
			{
				cout << "[ERROR_LINE]wrong line input\n" << line << endl;
//				throw "wrong line input";
				this->filter_flag=true;
				break;
			}
			key = line.substr(posb, pose-posb);
			posb = pose + 1;
			if(posb >= line.size())
			{
				cout << "[ERROR_LINE]wrong line input\n" << line << endl;
//				throw "wrong line input";
				this->filter_flag=true;
				break;
			}
			pose = line.find_first_of(spliter, posb);
			value = stod(line.substr(posb, pose-posb));
			if(value != 0)
			{
				size_t tmp_pose = key.find_first_of("=", 0);
				if(posb != string::npos)
				{
					string k=key.substr(0, tmp_pose);
					map_feature[k]=key
				}

				this->x.push_back(make_pair(key, value));
			}
		}
		if (combineFeatures.size()>0)
		{
			 for(int i = 0; i < combineFeatures.size(); ++i)
			 {
				 vector<string> local_combine_feature=combineFeatures[i];
				 string feature="combine_";
				 for (int j = 0; j < local_combine_feature.size(); ++j)
				 {
					 string local_key=local_combine_feature[j];
					 iter=map_feature.find(local_key);
					 if (iter != mapStudent.end())
					 {
						 feature+=iter.second();
					 }
					 else
					 {
						 feature+=local_key+"=none";
					 }
				 }
				 this->x.push_back(make_pair(feature, 1.0));
			 }
		}

	}
	catch (string e)
	{
		cout <<"[ERROR_LINE]Error wrong line input: " << line << " ----" <<e << endl;
		this->filter_flag=true;
	}
	catch (exception& e)
	{
		cout <<"[ERROR_LINE]Error wrong line input: " << line << " ----" <<e.what() << endl;
		this->filter_flag=true;
	}
}


#endif /*FM_SAMPLE_H_*/

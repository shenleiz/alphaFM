#ifndef FM_SAMPLE_H_
#define FM_SAMPLE_H_

#include <string>
#include <vector>
#include <exception>
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


fm_sample::fm_sample(const string& line) 
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
				this->x.push_back(make_pair(key, value));
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

#include <iostream>
#include <fstream>
#include <queue>
#include <map>

 using namespace std;
 
 void openFile(ifstream& f,string fileName);
 void fillPref(vector<vector<int> >& prefList,ifstream& f,int size);
 bool find(map<int,int> couples, int woman);
 bool comparePref(vector<int> womenPref, int man, int exMan);
 
 int main(int argc,const char *argv[]){
 	queue<int> singles;
 	map<int,int> couples;
 	vector<vector<int> > menPref;
 	vector<vector<int> > womenPref;
 	vector<int> lastPref;
 	int size,exman;
 	int pref;
 	
 	ifstream menStream,womenStream;
 	openFile(menStream,"preference_m.txt");
 	menStream >> size; 	
 	for(int i=0;i < size;i++){
 		singles.push(i);		
		lastPref.push_back(0);
	}		
 	fillPref(menPref,menStream,size);
 	
 	openFile(womenStream,"preference_w.txt");
 	womenStream >> size;
 	fillPref(womenPref,womenStream,size);
 	
 	menStream.close();
 	womenStream.close(); 	
 	
 	while(!singles.empty()){	
	 	pref = lastPref[singles.front()]; 
		cout << "man " << singles.front() << " proposes woman " << menPref[singles.front()][pref] << endl;
 		if(!find(couples, menPref[singles.front()][pref])){  			
 			cout << "matched - no previous partner available" << endl << endl;
 			couples.insert(pair<int,int>(menPref[singles.front()][pref],singles.front()));
			lastPref[singles.front()]++;  		
 			singles.pop();			
 		}
 		else if(comparePref(womenPref[menPref[singles.front()][pref]], singles.front(), couples[menPref[singles.front()][pref]])){  			
 			cout << "matched - proposer is a higher preference for woman " << menPref[singles.front()][pref] << endl ; 			
 			exman = couples[menPref[singles.front()][pref]];
 			cout << "man " << exman << " is single again" << endl << endl;
 			couples[menPref[singles.front()][pref]] = singles.front(); 
			lastPref[singles.front()]++; 			
 			singles.pop();
 			singles.push(exman); 				
 		}
		else{	
			lastPref[singles.front()]++; 			
			cout << "No match" << endl;						
		}
	 }
	 cout << "Matching:" << endl;
	 
	 for(int i = 0;i < size ; i++){
	 	for(map<int,int>::iterator it = couples.begin(); it != couples.end(); ++it)
	 		if(it -> second == i)
	 			cout << "man " << it->second << " --> " << "woman " << it -> first << endl;	
	 }	
	 
 }
 
 void openFile(ifstream& f,string fileName){		
	f.open(fileName.c_str());		
	
	while(!f.is_open()){	 
		cout << fileName << " could not be opened - Enter again" << endl;
		cin >> fileName;
		f.open(fileName.c_str());
	}
}

void fillPref(vector<vector<int> >& prefList,ifstream& f,int size){	
	prefList.resize(size);
	for(int i=0;i < size; i++) {
		prefList[i].resize(size);		
		for(int j=0;j < size;j++){
			f >> prefList[i][j];
			//cout <<	prefList[i][j] << " ";
		}
	}
}

bool find(map<int,int> couples, int woman){
	bool result = false;
		for(map<int,int>::iterator it = couples.begin(); it != couples.end(); ++it) {
			if(it -> first == woman)
				result = true;
	}	
	return result;
}

 bool comparePref(vector<int> womenPref, int man, int exMan){ 	
 	int first,second;
	for(int i= 0; i < womenPref.size() ; i++){	
		if( womenPref[i] == man)
			first = i;
		if( womenPref[i] == exMan)
			second = i;
	}
	return first < second;
}
	
 

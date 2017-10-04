#include<bits/stdc++.h>
#include<unistd.h>
#include<string>
using namespace std;

typedef struct subj_struct {
    int elective;

    string s_sub[3];
    int teacher[3];
    string s_teacher[3];
} sec_subj;
sec_subj waste;


sec_subj v[10][5][5];
sec_subj sec_teacher[10][7];
int avail_teacher[4000][5][5];
int hours_left[10][7];

string IntToString(int a) {
    ostringstream temp;
    temp << a;
    return temp.str();
}

int find_sec(int ts) {
    return (ts % 10);
}

int find_day(int ts) {
    int x = find_sec(ts);
    return (ts - x) / 40;
}
int find_day_lab(int ts)
{
	return ts/10;
}

int find_slot(int ts) {
    int x = find_sec(ts);
    x = (ts - x) % 40;
    return x / 10;
}

int all_hrs_finished() {
    int flag = 1;
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 7; i++) {
            if (hours_left[j][i] > 0) {
                flag = 0;
                break;
            }
        }
    }
    return flag;
}

void all_hrs_finished_print() {
    int flag = 1;
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 7; i++) {
            cout << hours_left[j][i] << endl;
        }
    }
}

int free_or_not(int sec, int sub, int slot, int day) {
    if (sec_teacher[sec][sub].elective > 0) {
        int k = sec_teacher[sec][sub].elective;
        int flag = 0;
        for (int i = 0; i < k; i++) {
            if (avail_teacher[sec_teacher[sec][sub].teacher[i]][day][slot] != -1)
                flag = 1;
        }
        if (flag == 0)
            return 1;
    } else {
        if (avail_teacher[sec_teacher[sec][sub].teacher[0]][day][slot] == -1)
            return 1;
    }
    return 0;
}

int count_hr(int sub, int ts,int f) {
    int c = 0;
    int slot = find_slot(ts);
;
    int day = find_day(ts);
    int sec = find_sec(ts);
        if(f==1){
    	slot=4;
    	day=find_day_lab(ts);
    }

    for (int i = 0; i < slot; i++) {
        if (v[sec][day][i].s_sub[0] == sec_teacher[sec][sub].s_sub[0]) {
            c++;
        }
    }
    return c;
}

int is_Safe(int sub, int ts,int f) {
    int slot = find_slot(ts);
    int day = find_day(ts);
    int sec = find_sec(ts);
    if(f==1){
    	slot=4;
    	day=find_day_lab(ts);
    }


    if (hours_left[sec][sub] == 3) {
        int a = free_or_not(sec, sub, slot, day);
        return a;
    } else if (hours_left[sec][sub] == 2) {
        if (v[sec][day][slot].s_sub[0] == sec_teacher[sec][sub].s_sub[0] && slot != 2) {
            return free_or_not(sec, sub, slot, day);
        } else if (count_hr(sub, ts,f) == 0) {
            return free_or_not(sec, sub, slot, day);
        }
    } else if (hours_left[sec][sub] == 1) {
    	if(f==1){
    		return free_or_not(sec, sub, slot, day);
    	}
    	else{

        if (v[sec][day][slot - 1].s_sub[0] == sec_teacher[sec][sub].s_sub[0] && slot != 2) {
            if (count_hr(sub, ts,f) == 1) {
                return free_or_not(sec, sub, slot, day);
            }
        }
        if (count_hr(sub, ts,f) == 0) {
            return free_or_not(sec, sub, slot, day);
        }
    	}
    }
    return 0;
}

int algo(int ts,int f) {
    if (all_hrs_finished()) {
    	cout<<f<<" yes";
    	cout<<ts<<endl;
        return 1;
    }
    //printf("%d\n",ts);
    int day = find_day(ts);
    int sec = find_sec(ts);
    int slot = find_slot(ts);
    if(f==1){
    	slot=4;
    	day=find_day_lab(ts);
    }
    for (int sub = 0; sub < 7; sub = sub + 1) {
        if (is_Safe(sub, ts,f)) {

            sec_subj p = sec_teacher[sec][sub];
            hours_left[find_sec(ts)][sub]--;


            v[sec][day][slot] = p;

            cout<<sec<<" " <<p.s_sub[0]<<endl;
            if (sec_teacher[sec][sub].elective > 0) {
                int k = sec_teacher[sec][sub].elective;
                int flag = 0;
                for (int i = 0; i < k; i++) {
                    avail_teacher[sec_teacher[sec][sub].teacher[i]][day][slot] = ts;
                }

            } else {
                avail_teacher[sec_teacher[sec][sub].teacher[0]][day][slot] = ts;
            }

            if (algo(ts + 1,f)) {

                return 1;
            }
            if (sec_teacher[sec][sub].elective > 0) {
                int k = sec_teacher[sec][sub].elective;
                int flag = 0;
                for (int i = 0; i < k; i++) {
                    avail_teacher[sec_teacher[sec][sub].teacher[i]][day][slot] = -1;
                }
            } else {
                avail_teacher[sec_teacher[sec][sub].teacher[0]][day][slot] = -1;
            }
            v[sec][day][slot] = waste;
            hours_left[find_sec(ts)][sub]++;
        }
    }
    return 0;
}

void print_timetable() {

    map<int, string>m_day;
    m_day[0] = "MONDAY";
    m_day[1] = "TUESDAY";
    m_day[2] = "WEDNESDAY";
    m_day[3] = "THURSDAY";
    m_day[4] = "FRIDAY";

    for (int sec = 0; sec < 10; sec++) {
        string tmp = "test" + IntToString(sec) + ".txt";
        char *q = const_cast<char*> (tmp.c_str());
        ofstream outfile(q);
        ofstream out;
        out.open(q);
        for (int day = 0; day < 5; day++) {
            out << m_day[day] << ";";

map<int, string>m_day;
    m_day[0] = "MONDAY";
    m_day[1] = "TUESDAY";
    m_day[2] = "WEDNESDAY";
    m_day[3] = "THURSDAY";
    m_day[4] = "FRIDAY";
            for (int slot = 0; slot < 5; slot++) {
                //if (v[sec][day][slot].elective == 0)
                  //  out << "$";
                /*else*/ if (v[sec][day][slot].elective == -1 || v[sec][day][slot].elective == 0 ) {
                    out << v[sec][day][slot].s_sub[0] + " " << v[sec][day][slot].s_teacher[0];
                } else if (v[sec][day][slot].elective > 0) {
                    int k = v[sec][day][slot].elective;

                    for (int q = 0; q < k; q++) {
                        out << v[sec][day][slot].s_sub[q] + " (" << v[sec][day][slot].s_teacher[q] << " )";
                        out << "!";
                    }
                }
                out << ";";
            }
            out << "\n";
        }
    }

}

int find_s(int ts, int t){
    sec_subj a = v[find_sec(ts)][find_day(ts)][find_slot(ts)];
    for( int i = 0; i < 3; i++){
        if ( a.teacher[i] == t)
            return i;
    }
    return 0;
}

string getName(int i){
    sec_subj a;
    int ts = 0;
    for ( int j = 0; j < 5; j++){
        for ( int k = 0; k < 4; k++){
            if (avail_teacher[i][j][k] != -1 ){
                ts = avail_teacher[i][j][k];
                break;
            }
        }
        if (ts != 0) break;
    }
    a=v[find_sec(ts)][find_day(ts)][find_slot(ts)];
    int indexx = find_s(ts, i);
    return a.s_teacher[indexx];
}

string find_batch(int num){
    switch(num){
    case 0:
        return "B.Tech(I.T)1st Year SEC 1!";
    case 1:
        return "B.Tech(I.T)1st Year SEC 2!";
    case 2:
        return "B.Tech (ECE)1st Year!";
    case 3:
        return "B.Tech(I.T)2nd Year SEC 1!";
    case 4:
        return "B.Tech(I.T)2nd Year SEC 2!";
    case 5:
        return "B.Tech(ECE) 2nd Year!";
    case 6:
        return "B.Tech(I.T) 3rd Year SEC 1!";
    case 7:
        return "B.Tech(I.T) 3rd Year SEC 2!";
    case 8:
        return "B.Tech(ECE) 3rd Year!";
    case 9:
        return "B.Tech(I.T) 4th Year!";
    default:
        return "";
    }

}

void prinf_teacher()
{

map<int, string>m_day;
    m_day[0] = "MONDAY";
    m_day[1] = "TUESDAY";
    m_day[2] = "WEDNESDAY";
    m_day[3] = "THURSDAY";
    m_day[4] = "FRIDAY";

    		ofstream outfile("teacher.txt");
	  ofstream out;
    out.open("teacher.txt");

    for(int i=0;i<43;i++)
    {   	out<<"Teacher: "<<getName(i)<<";"<<endl;

    	for(int j=0;j<5;j++)
    	{
    		out<<m_day[j]<<";";
    		for(int k=0;k<5;k++)
    		{
    			if(avail_teacher[i][j][k]== -1)
    			{
    				out<<"F"<<";";
    				continue;
    			}
    			int indexx = find_s(avail_teacher[i][j][k], i);
    			int ts = avail_teacher[i][j][k];
    			sec_subj pp = v[find_sec(ts)][find_day(ts)][find_slot(ts)];
    			out<<find_batch(find_sec(ts))<<"("<<pp.s_sub[indexx]<<")"<<";";
    		}
    		out<<"\n";
    	}
    }
}
void find_compulsory(int x[10])
{

	for(int i=0;i<10;i++)
		x[i]=0;
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<7;j++)
		{
			if(sec_teacher[i][j].elective==-1)
			{
				////cout<<sec_teacher[i][j].s_sub[0]<<" "<<sec_teacher[i][j].s_sub[0][sec_teacher[i][j].s_sub[0].length()-2]<<endl;
				if(sec_teacher[i][j].s_sub[0][sec_teacher[i][j].s_sub[0].length()-2]=='2'){

					x[i]++;
				}

			}

		}
	}

}

int main(int argc, char** argv) {
    int la = 50;
    string s;
    waste.s_sub[0] = "faltu";
    waste.elective = -2;
    for (int l = 0; l < 10; l++) {
        for (int m = 0; m < 7; m++) {
            sec_teacher[l][m].elective = -2;
            for (int z = 0; z < 3; z++) {
                stringstream ss;
                ss << (100 * l + 10 * m + z);
                s = ss.str();
                sec_teacher[l][m].s_sub[z] = "null" + s;
                sec_teacher[l][m].teacher[z] = la++;
                sec_teacher[l][m].s_teacher[z] = "  ";
            }
        }
    }
    string sss="";
    for(int i=1;i<argc;i++){
    	string xxx(argv[i]);
    	if(i==1)
    		sss=sss+xxx;
    		else
    	sss=sss+" "+xxx;
	}
	//cout<<sss<<endl;
	char * S = new char[sss.length() + 1];
	strcpy(S,sss.c_str());
	//cout<<S;

    ifstream inp_file;
    inp_file.open(S);
    int c;
    int sec;
    int no_subj;
    int j;
    for (int i = 0; i < 10; i++) {
        inp_file >> sec >> no_subj;

        j = 0;
        if (no_subj == 5) {
            sec_teacher[i][0].elective = 0;
            sec_teacher[i][6].elective = 0;
            j++;
            no_subj++;
        } else if (no_subj == 6) {
            sec_teacher[i][6].elective = 0;
        }
        for (; j < no_subj; j++) {
            inp_file >> c >> sec_teacher[i][j].elective;

            if (sec_teacher[i][j].elective == -1) {
                inp_file >> sec_teacher[i][j].s_sub[0];
                inp_file >> sec_teacher[i][j].teacher[0];
                inp_file >> sec_teacher[i][j].s_teacher[0];
            } else {
                for (int k = 0; k < sec_teacher[i][j].elective; k++) {
                    inp_file >> sec_teacher[i][j].s_sub[k];
                    inp_file >> sec_teacher[i][j].teacher[k];
                    inp_file >> sec_teacher[i][j].s_teacher[k];
                }
            }
        }

    }
    /*//cout << sec_teacher[0][0].s_sub[0]<<endl;
    //cout << sec_teacher[0][0].elective<<endl;
*/
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            hours_left[i][j] = 3;
        }
    }
    for (int i = 0; i < 10; i++) {
        hours_left[i][6] = 2;
    }
    for (int i = 0; i < 4000; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++)
                avail_teacher[i][j][k] = -1;
        }
    }

    clock_t start = clock();
    int a = algo(0,0);
    clock_t stop = clock();
   // //cout<<"sd"<<endl;


 ////cout<<"sd"<<endl;
 int x[10];
 find_compulsory(x);
 for(int i=0;i<10;i++)
	 //cout<<x[i]<<" ";
 //cout<<endl;
 for (int i = 0; i < 10; i++) {
     for (int j = 0; j < 7; j++) {
         hours_left[i][j] = 0;
     }
 }
int p=1000;
 for(int i=0;i<10;i++)
 {
	 for(int j=0;j<7;j++){
	 if(sec_teacher[i][j].s_sub[0][sec_teacher[i][j].s_sub[0].length()-2]=='2'){
	 	sec_teacher[i][j].elective = -1;
		 hours_left[i][j]=1;
		}
	 
	 else
	 {	
	 	sec_teacher[i][j].elective = -2;


	 	for (int z = 0; z < 3; z++) {
         stringstream ss;

         ss << (1000 * i + 100 * j + z+5);
         s = ss.str();
         sec_teacher[i][j].s_sub[z] = "null" + s;
         sec_teacher[i][j].teacher[z] = p++;
         sec_teacher[i][j].s_teacher[z] = "  ";
	 }
	 }
	 }
 }
 for(int i=0;i<10;i++)
 {
	 int q=x[i];
	 q=5-q;
	 for(int j=0;j<7;j++)
	 {
		 if(q==0)
			 break;
		 if(hours_left[i][j]==0)
		 {
			 hours_left[i][j]=1;
			 sec_teacher[i][j].elective=0;

			 q=q-1;
		 }
	 }
 }

all_hrs_finished_print();
int pp=algo(0,1);
 for(int i=0;i<10;i++)
 {
	 for(int j=0;j<5;j++){

		 cout<<v[i][j][4].s_sub[0]<<endl;

	 }
	 cout<<endl;
 }
 print_timetable();
prinf_teacher();
all_hrs_finished_print();
    return 0;
}
#include <bits/stdc++.h>
#include <iomanip> //library for table
using namespace std;

//Khai bao struct
struct Student {
	//Attribute
	string studentID;
	string fullName;
	string DoB;
	float AlgebraScore;
	float CalculusScore;
	float BPScore;

	//Function
	//Format name from Ho-Ten -> Ten-Ho
	string lastName;
	string firstName;
	
	string formatName(string fullName) {
        stringstream ss(fullName);              // Tách chuỗi bằng khoảng trắng
        vector<string> parts;
        string word;
        
        while (ss >> word){ // Đọc từng từ trong tên
            parts.push_back(word); // Lưu vào mảng `parts`
        }                      
                         
        string formatted = parts.back();        // Lấy phần tử cuối (tên) làm đầu
        lastName = parts.back();
        firstName = "";
        for (int i = 0; i < parts.size() - 1; i++) {
            formatted += " " + parts[i];        // Nối các phần còn lại vào sau
            firstName += parts[i] + " ";
        }
    
        return formatted;
    }
    	
	float GPA() {
		return (AlgebraScore + CalculusScore + BPScore) / 3;
	}

	//Input student infor
	void inputStudentInfor() {
		cout << "   ID: ";
		getline(cin, studentID);

		cout << "   Full Name: ";
		getline(cin, fullName);

		cout << "   DoB: ";
		getline(cin, DoB);

		cout << "   Algebra Score: ";
		cin >> AlgebraScore;
		cout << "   Calculus Score: ";
		cin >> CalculusScore;
		cout << "   BP Score: ";
		cin >> BPScore;
		cin.ignore(); // Delete \n after cin
	}

	//Print Student list as table
	void showStudentInfor() {
		cout << left
		     << setw(20) << studentID
		     << setw(50) << formatName(fullName)
		     << setw(20) << firstName
		     << setw(20) << lastName
		     << setw(20) << DoB
		     << setw(20) << AlgebraScore
		     << setw(20) << CalculusScore
		     << setw(20) << BPScore
		     << setw(20) << fixed << setprecision(2) << GPA() << endl;
	}
	
	//Save student infor to text file
    void saveStudentInfor(ofstream &write) {
        write   << left
                << setw(20) << studentID
                << setw(50) << fullName
                << setw(20) << DoB
                << setw(20) << AlgebraScore
                << setw(20) << CalculusScore
                << setw(20) << BPScore
                << setw(20) << fixed << setprecision(2) << GPA() << endl;
    }
	
};

//Find Student Highest GPA
void StudentHighestGPA(Student ds[], int n){
    int idx_max = 0;
    float GPA_highest = ds[idx_max].GPA();
    for(int i = 0; i <= n - 1; i++){
        if(ds[i].GPA() > GPA_highest){
            GPA_highest = ds[i].GPA();
            idx_max = i;
        }
    }
    cout << "Student has highest GPA is: " << idx_max + 1 << " th!" << endl;
}

//Find Student Lowest GPA
void StudentLowestGPA(Student ds[], int n){
    int idx_min = 0;
    float GPA_lowest = ds[idx_min].GPA();
    
    for(int i = 0; i <= n - 1; i++){
        if(ds[i].GPA() < GPA_lowest){
            GPA_lowest = ds[i].GPA();
            idx_min = i;
        }
    }
    cout << "Student has lowest GPA is: " << idx_min + 1<< " th!" << endl;
}

//Find student Highest BP Score
void StudentHighestBPScore(Student ds[], int n){
    int idx_BPmax = 0;
    float BPScoce_Max = ds[idx_BPmax].BPScore;
    
    for(int i = 0; i <= n - 1; i++){
        if(ds[i].BPScore > BPScoce_Max){
            BPScoce_Max = ds[i].BPScore;
            idx_BPmax = i;
        }
    }
    cout << "Student has highest BP Score is: " << idx_BPmax + 1<< " th!" << endl;
}

//Convert dd/mm/yyyy => yyyymmdd
int standardizeDate(string dob) {
    // dob = "20/03/2004"
    string day = dob.substr(0, 2); //cat 2 kytu tu vi tri so 0
    string month = dob.substr(3, 2);
    string year = dob.substr(6, 4);
    string new_date = year + month + day; // "20040320"
    return stoi(new_date); //convert to int
}

//Find Oldest student
void oldestStudent(Student ds[], int n){
    int idx_oldest = 0;
    int oldest_std = standardizeDate(ds[idx_oldest].DoB);
    
    for(int i = 0; i <= n - 1; i++){
        if(standardizeDate(ds[i].DoB) < oldest_std){
            oldest_std = standardizeDate(ds[i].DoB);
            idx_oldest = i;
        }
    }
    cout << "The oldest Student is " << ds[idx_oldest].studentID << " " << ds[idx_oldest].fullName << " " << ds[idx_oldest].DoB << endl; 
}

//Find Yougest student
void youngestStudent(Student ds[], int n){
    int idx_youngest = 0;
    int youngest_std = standardizeDate(ds[idx_youngest].DoB);
    
    for(int i = 0; i <= n - 1; i++){
        if(standardizeDate(ds[i].DoB) > youngest_std){
            youngest_std = standardizeDate(ds[i].DoB);
            idx_youngest = i;
        }
    }
    cout << "The youngest Student is " << ds[idx_youngest].studentID << " " << ds[idx_youngest].fullName << " " << ds[idx_youngest].DoB << endl; 
}

//Search Student by ID
void searchStudentID(string stdID, Student ds[], int n){
    bool canFind = false;
    for(int i = 0; i <= n - 1; i++){
        if(stdID == ds[i].studentID){
            canFind = true;
        	cout << left
        	     << setw(20) << "studentID"
        	     << setw(50) << "fullName"
        	     << setw(20) << "firstName"
        	     << setw(20) << "lastName"
        	     << setw(20) << "DoB"
        	     << setw(20) << "AlgebraScore"
        	     << setw(20) << "CalculusScore"
        	     << setw(20) << "BPScore"
        	     << setw(20) << fixed << setprecision(2) << "GPA" << endl;
    	     
            ds[i].showStudentInfor();
            break;
        }
    }
    
    if(canFind == false){
        cout << "NO MATCHED ID FOUND!!" << endl;
    }
    
}

//Sort Student list by GPA with ascending order
void swap(int &a, int &b){
    float temp = a;
    a = b;
    b = temp;
}

void sortGPAAscent(Student ds[], int n){
    //Selection sort
    for(int i = 0; i <= n - 1; i++){
        int idx_min_GPA = i;
        float min_GPA = ds[idx_min_GPA].GPA();
        
        for(int j = i; j <= n - 1; j++){
            if(ds[j].GPA() < min_GPA){
                min_GPA = ds[j].GPA();
                idx_min_GPA = j;
            }
        }
        swap(ds[idx_min_GPA], ds[i]); //swap ca struct vi ds[i].GPA() la ket qua dc return ve => ko the swap
    }
    
    //Show student infor with Ascent Order
	cout << "Order Student with Ascent Order: " << endl;

	for(int i = 0; i <= n - 1; i++) {
		cout << i + 1 << ". " << ds[i].fullName << endl;
	}
}

//Sort Student list by GPA with descending order
void sortGPADescent(Student ds[], int n){
    //Selection sort
    for(int i = 0; i <= n - 1; i++){
        int idx_max_GPA = i;
        float max_GPA = ds[idx_max_GPA].GPA();
        
        for(int j = i; j <= n - 1; j++){
            if(ds[j].GPA() > max_GPA){
                max_GPA = ds[j].GPA();
                idx_max_GPA = j;
            }
        }
        swap(ds[idx_max_GPA], ds[i]); //swap ca struct vi ds[i].GPA() la ket qua dc return ve => ko the swap
    }
    
    //Show student infor with Descent Order
	cout << "Order Student with Descent Order: " << endl;

	for(int i = 0; i <= n - 1; i++) {
		cout << i + 1 << ". " << ds[i].fullName << endl;
	}
}

int main() {
	int n;
	cout << "Input the number of student: \nn = ";
	cin >> n;
	cin.ignore();

	//Create list of 1000 student
	Student ds[n];


	//Input information for n student
	for(int i = 0; i <= n - 1; i++) {
		cout << "Student " << i + 1 << "th information: \n";
		ds[i].inputStudentInfor();
	}

	//Show student infor
	cout << "=====STUDENT=====\n";
	cout << left
	     << setw(20) << "studentID"
	     << setw(50) << "fullName"
	     << setw(20) << "firstName"
	     << setw(20) << "lastName"
	     << setw(20) << "DoB"
	     << setw(20) << "AlgebraScore"
	     << setw(20) << "CalculusScore"
	     << setw(20) << "BPScore"
	     << setw(20) << "GPA" << endl;

	for(int i = 0; i <= n - 1; i++) {
		ds[i].showStudentInfor();
	}

	//Save student infor
	ofstream outFile("student_list.txt");
    outFile << "=====STUDENT=====\n";
	outFile << left
	     << setw(20) << "studentID"
	     << setw(50) << "fullName"
	     << setw(20) << "firstName"
	     << setw(20) << "lastName"
	     << setw(20) << "DoB"
	     << setw(20) << "AlgebraScore"
	     << setw(20) << "CalculusScore"
	     << setw(20) << "BPScore"
	     << setw(20) << "GPA" << endl;
	     
	if (outFile.is_open()) {
		for(int i = 0; i <= n - 1; i++) {
			ds[i].saveStudentInfor(outFile);
		}
		outFile.close();
		cout << "Save file success!" << endl;
	} else {
		cout << "Error when save file" << endl;
	}
	
	//Student highest GPA
	StudentHighestGPA(ds, n);
	//Student lowest GPA
	StudentLowestGPA(ds, n);
	//Student highest BPScore
	StudentHighestBPScore(ds, n);
    
    //Oldest Student
    oldestStudent(ds, n);
    youngestStudent(ds, n);
    
    //Search Student by ID
    string student_id;
    cout << "Search Studend ID: ";
    getline(cin, student_id);
    searchStudentID(student_id, ds, n);
    
    //Sort with Descent Order
    sortGPADescent(ds, n);
    
}
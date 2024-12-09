#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;

//grade class to add all info about grades
class Grade {
private:
	double grade;
public:
	// adding data to grade
	void addData() {
		cin >> grade;
		while (grade < 0 || grade > 100) {
			cin >> grade;
		}
}
	double getgradesforAVG() {
		return grade;
	}
	void display() {
		cout << grade << endl;
	}
	string getDataForFile() {
		return to_string(grade) + " ";
	}
	void loadDataFromFile(ifstream& file) {
		string GradeSTR;
		getline(file, GradeSTR);
		grade = stod(GradeSTR);
	}
};
// grade to add new student
class Student {
	private:
		string Name;
		string Email;
		string StudentID;
		string classify;
		double average = 0;
		double total = 0, TotalGrades =0;
		double FirstGrade = 0, SecondGrade =0, ThirdGrade =0, FourthGrade = 0, PredictedGrade;
		vector<Grade>grades; //store a list of grades
		Grade mark; // declaring an object to connect the classes Student and Grade
		
public:

	void addGrades()//add grade for user
	{
		for (int i = 0; i < 3; i++) {
			cout << " enter grade" << (i + 1) << ": ";
			mark.addData();
			grades.push_back(mark);//adding to vector
		}
		cout << " do you have the grade for the fourth assessment ? (y/n)" << endl;
		char ans;
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			cout << " enter grade4: ";
			mark.addData();
			grades.push_back(mark);//adding to vector
		}
		if (ans == 'n' || ans == 'N') {
			displayFourthGrade();
		}
		findAVG();
	}
	void addToExistingGrades()
		{
		mark.addData();
		grades.push_back(mark);
		}
	
	void updateGrade(int assessmentNumber) {
		if (assessmentNumber >= 1 && assessmentNumber <= grades.size()) { //validating the input
			cout << "Enter the new grade for assessment " << assessmentNumber << ": ";
			mark.addData();// getting the new grade
			grades[assessmentNumber - 1] = mark;
			cout << "Grade updated successfully!" << endl;
		}
		else {
			cout << "Invalid assessment number!" << endl;
		}
	}
	void addData() // getting students info
	{
		cout << "enter name: " << endl;
		getline(cin >> ws, Name);
		cout << "enter Email: " << endl;
		getline(cin >> ws, Email);
		cout << "enter student number: " << endl;
		getline(cin >> ws, StudentID);
	}
	
	void findAVG()
	{
		total = 0; // resets the total
		int numGrades = grades.size();
		if (numGrades > 0) {
			FirstGrade = (numGrades >= 1) ? (grades[0].getgradesforAVG()) * 0.1 : 0;
			SecondGrade = (numGrades >= 2) ? (grades[1].getgradesforAVG()) * 0.2 : 0;
			ThirdGrade = (numGrades >= 3) ? (grades[2].getgradesforAVG()) * 0.3 : 0;
			FourthGrade = (numGrades >= 4) ? (grades[3].getgradesforAVG()) * 0.4 : 0;
			average = FirstGrade + SecondGrade + ThirdGrade + FourthGrade;
		}
			
	}

	void AVGclassification() // using conditional statements to classify students based on their average
	{
		findAVG();
		 classify = (average >= 70) ? " First Class Honours" : (average >= 60) ? " Upper Second-Class Honours (2:1)" : (average >= 50) ? " Lower Second-Class Honours (2:2)" : (average >= 40) ? " Third Class Honours" : " Failed";
	}
	void CalculateFourthGrade2() // predicting the required grade for 4th assignment to get overall of 70%
	{
		FirstGrade = (grades[0].getgradesforAVG()) * 0.1;
		SecondGrade = (grades[1].getgradesforAVG()) * 0.2;
		ThirdGrade = (grades[2].getgradesforAVG()) * 0.3;
		total = FirstGrade + SecondGrade + ThirdGrade;
		PredictedGrade = ((70 - total)/ 0.4);
	}

	//function to return the data
	string getName() 
	{
		return Name;
	}
	string getEmail() 
	{
		return Email;
	}
	string getStudenId()
	{
		return StudentID;
	}
	vector<Grade> getGrades() {
		return grades;
	}
	
	string getAVG() 
	{
		return to_string(average) + " ";
	}
	string getClassification()
	{
		return classify;
	}
	string getpredictedGrade()
	{
		return to_string(PredictedGrade) + " ";
	}
	
	void displayAVG() {

		findAVG();
			cout << average << endl;

	}
	void displayFourthGrade() {
		CalculateFourthGrade2();
		cout << "The grade " << Name <<  " needs to achieve in the fourth assessment to get average of 70% is at least: " << PredictedGrade << endl;
	}
	void printGrades() {
		for (int i = 0; i < grades.size(); i++) {
			cout << "Grade" << (i + 1) << ": ";
			grades[i].display();

		}
	}
	void display()
	{ 
		cout << "Student name: " << Name << endl;
		cout << "student number: " << StudentID << endl;
		cout << "email: " << Email << endl;
		printGrades();
		findAVG();
		AVGclassification();
		cout << "average is: " << average << classify << endl;
		
	}
	void edit() //editing function
	{
		//maybe add a eature that the person canchoose to change only a part of it not go through each step
		cout << "enter new name: " << endl;
		getline(cin >> ws , Name);
		cout << "enter new email: " << endl;
		getline(cin >> ws, Email);
		cout << "enter new student number: " << endl;
		getline(cin >> ws, StudentID);
	}
	void LoadDataFromFile(ifstream& file) 
	{
		getline(file, Name);
		getline(file, Email);
		getline(file, StudentID);
		string averageSTR;
		getline(file, averageSTR);
		/*when average was written to the file it was converted to string so when we load it we need to get the variable as a string and the convert it to double*/
		average = stod(averageSTR);
		getline(file, classify);
		//getting te grades from the file
		bool MoreGrade;
		Grade markobj;
		while (MoreGrade = true) {
			markobj.loadDataFromFile(file); //calling the function from the grade class
			grades.push_back(markobj); // adding new grade
			streampos oldpos = file.tellg(); // gives the current location in the file
			string checkEnding;// dedicating a variable to check wether it has reached the end of file or not
			getline(file, checkEnding);
			if (checkEnding == "LastLineYay") {
				MoreGrade = false;
				break;
			}
			else {
				file.seekg(oldpos); // continues getting the new info from that position until it reaches the "lastlineyay"
			}
		 }
	}
};

// writing the menu 
class Menu {
private:
	int option;
	int numberInput;
	vector<Student> students; // holds every student
	bool choose = true;
	//printing a studets record
	void printstudentvector()
	{
		for (int i = 0; i < students.size(); i++)
		{
			cout << (i + 1) << " " << students[i].getName() << endl;
		}
	}
	void printstudentvectorII()
	{
		cout << "Student: "<< "\t"<< "Average" << endl;
		for (int i = 0; i < students.size(); i++)
		{
			Student studentobj;
			studentobj.findAVG();
			
			cout << (i + 1) << ". " << students[i].getName() << ": \t"  << students[i].getAVG() << endl;

		}
	}
	void bubbleSort() {
		Student test;

		for (int i = 0; i < (students.size() - 1); ++i) {
			for (int j = i + 1; j < students.size(); ++j) {
				if (stod(students[i].getAVG()) <  stod(students[j].getAVG())){
					test = students[i];
					students[i] = students[j];
						students[j] = test;
				}
			}
		}
	}
	//add new student function
	void addNewStudent()
	{
		Student Students; //calling an object
		Students.addData();
		students.push_back(Students); // adding the new student to the vector
	}
	//add new grade for a student
	void addNewGrade()
	{
		cout << "which student you ant to add anew grade for ? " << endl;
		printstudentvector();
		cin >> numberInput;
		students[numberInput - 1].addGrades();
	}
	void findingAverage() {
		cout << "which student average would you like to see? " << endl;
		printstudentvector();
		cin >> numberInput;
		students[numberInput - 1].displayAVG();
	}
	void findingFourthGrade() {
		cout << "which student average would you like to see? " << endl;
		printstudentvector();
		cin >> numberInput;
		students[numberInput - 1].displayFourthGrade();
	}

	void displayStudent()
	{
		cout << "choose a student which you would like to see more information about: " << endl;
		printstudentvectorII(); // printing the list of students
		cin >> numberInput;
		students[numberInput - 1].display();
	}
	void EditStudent()
	{
		cout << "which student would you like to edit? " << endl;
		printstudentvector();
		cin >> numberInput;
		students[numberInput - 1].edit(); // calling the edit function in the student class for a specific student in the vector
	}
	void updateGradeForStudent()
	{
		cout << "Choose a student to update the grade for: " << endl;
		printstudentvector();
		cin >> numberInput;

		if (numberInput >= 1 && numberInput <= students.size()) {
			int choice;
			cout << "1. Add new grade" << endl;
			cout << "2. Update existing grade" << endl;
			cout << "enter your choice";
			cin >> choice;
			switch (choice) {
			case 1:
				students[numberInput - 1].addToExistingGrades();
				break;
			case 2:

				cout << "Choose the assessment number to update the grade for: " << endl;
				students[numberInput - 1].printGrades();
				int assessmentNumber;
				cin >> assessmentNumber;
				students[numberInput - 1].updateGrade(assessmentNumber);
				break;

			default: 
				cout << "invalid choice" << endl;
			}
		}
		else {
			cout << "Invalid student number!" << endl;
		}
	}
	void WriteToFile()
	{
		ofstream outputFile; // creating the fileobject
		outputFile.open("studentmarks.txt"); //opening the file
			for (int i = 0; i < students.size(); i++) 
	        {
				outputFile << students[i].getName() << endl;
				outputFile << students[i].getEmail() << endl;
				outputFile << students[i].getStudenId() << endl;
				outputFile << students[i].getAVG() << endl;
				outputFile << students[i].getClassification();
				for (auto y : students[i].getGrades())
				{
					outputFile << y.getDataForFile() << endl;
				}
				outputFile << "LastLineYay"; // seperating each student info by seting checkpoint

				if (i != (students.size() - 1))
				{
					outputFile << endl;
				}
			}
		}

	void loadFromFile()
	{
		Student studentobj;
		ifstream inputFile;
		inputFile.open("studentmarks.txt"); //opening file 
		if (inputFile)
		{
			
			while (!inputFile.eof())
			{
				studentobj.LoadDataFromFile(inputFile);  //loading data from the file
				students.push_back(studentobj); //add the students to the vector
				}
			}
		}

	void saveAndQuit()
	{
		WriteToFile();
		choose = false;
		cout << "Goodbye!" << endl;
	}


public:
	
	void start() {
		while (choose) {
			
			cout << "|----------------------------------------------------------------------|" << endl;
			cout << "|Choose from the menu provided below:                                  |" << endl;
			//showing the menu to the user
			cout << "|----------------------------------------------------------------------|" << endl;
			cout << "|1. Add a new studnt                                                   |" << endl;
			cout << "|2. Add a student's grade                                              |" << endl;
			cout << "|3. edit students grade                                                |" << endl;
			cout << "|4. Load the students list and show a student's information            |" << endl;
			cout << "|5. Edit the student information                                       |" << endl;
			cout << "|6. Calculate Average                                                  |" << endl;
			cout << "|7. predict grade                                                      |" << endl;
			cout << "|8. Save data to file                                                  |" << endl;
			cout << "|9. load from file                                                     |" << endl;
			cout << "|10.Save the data and quit                                             |" << endl;
			cout << "|----------------------------------------------------------------------|" << endl;
			
			

			cin >> option;
			//using while loop to validate the user's input
			while (option < 1 || option > 10) {
				cout << "invalid input! try again" << endl;
				cin >> option;
			}
			switch (option) {
			case 1:
				addNewStudent();
				break;
			case 2:
				addNewGrade();
				break;
			case 3:
				updateGradeForStudent();
				break;
			case 4:
				bubbleSort();
				displayStudent();
				break;
			case 5:
				EditStudent();
				break;
			case 6:
				findingAverage();
				break;
			case 7 :
				findingFourthGrade();
				break;
			case 8:
				WriteToFile();
				cout << "Data was successefully saved to the file." << endl;
				break;
			case 9:
				loadFromFile();
				cout << " data was loaded from the file successfully! " << endl;
				break;
			case 10:
				saveAndQuit();
				break;
			}
		}
	}
};

int main() {
	//getting the menu class and from there each class will be called in each setion without calling them in the main
	Menu menu;
	menu.start();
}

// Include the includes.h header file from the parent directory
#include "../includes.h"

// Struct to represent a Question with text and choices
struct Question {
    string text;
    string choices;
};

// Function to run the quiz
int quiz() {
    int choi; // user's choice
    welcome("quiz"); // display a welcome message for the quiz

    // Get user's choice
    cin >> choi;

    if (choi == 1) {
        int correctAnswers = 0; // count of correct answers
        ifstream file("questions.txt"); // input file stream for questions
        ifstream file2("questions-choices.txt"); // input file stream for choices

        clear(); // clear the console

        // Check if files can be opened
        if (!file || !file2) {
            cerr << "Error: Unable to open questions.txt or questions-choices.txt file." << endl;
            return 0; // exit with error code
        }

        // Read questions and choices into a vector of Question objects
        vector<Question> questions;
        string line, lineChoice;
        while (getline(file, line) && getline(file2, lineChoice)) {
            Question q;
            q.text = line;
            q.choices = lineChoice;
            questions.push_back(q);
        }
        file.close();
        file2.close();

        // Shuffle the questions vector using Mersenne Twister random number generator
        random_device rd;
        mt19937 g(rd());
        shuffle(questions.begin(), questions.end(), g);

        // Display the first 5 questions and get user input
        for (int i = 0; i < 5; i++) {
            Question q = questions[i];
            string question = q.text;
            string choice = q.choices;
            int answerIndex = question.length() - 1;
            char correctAnswer = question[answerIndex];
            cout << "    " << question.substr(0, answerIndex) << endl; // Display the question

            // Display the choices
            cout << "      " << choice << endl;
            int userChoice;
            cin >> userChoice;

            // Evaluate the user's choice
            if (userChoice >= 1 && userChoice <= 3) {
                int int_correctAnswer = atoi(&correctAnswer);
                //char userAnswer = 'a' + userChoice - 1;
                if (int_correctAnswer == userChoice) {
                    correctAnswers++;
                    //cout << "Great Work!" << endl;
                }
            } else {
                cout << "      Invalid choice. Please enter 1, 2, or 3." << endl;
                i--; // Repeat the same question
            }
        }

        return correctAnswers; // return the number of correct answers
    } else {
        return 404; // return error code if user chooses not to play
    }
}
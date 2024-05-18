#include "../includes.h"

struct Question {
    string text;
    string choices;
};

int quiz() {
    int choi;
    welcome("quiz");

    cin >> choi;

    if (choi == 1)
    {
        int correctAnswers = 0;
        ifstream file("questions.txt");
        ifstream file2("questions-choices.txt");

        clear();

        if (!file || !file2)
        {
            cerr << "Error: Unable to open questions.txt or questions-choices.txt file." << endl;
            return (0);
        }

        // Read questions and choices into a vector of Question objects
        vector<Question> questions;
        string line, lineChoice;
        while (getline(file, line) && getline(file2, lineChoice))
        {
            Question q;
            q.text = line;
            q.choices = lineChoice;
            questions.push_back(q);
        }
        file.close();
        file2.close();

        // Shuffle the questions vector
        random_device rd;
        mt19937 g(rd());
        shuffle(questions.begin(), questions.end(), g);

        // Display the first 5 questions and get user input
        for (int i = 0; i < 5; i++)
        {
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
            if (userChoice >= 1 && userChoice <= 3)
            {
                int int_correctAnswer = atoi(&correctAnswer);
                //char userAnswer = 'a' + userChoice - 1;
                if (int_correctAnswer == userChoice)
                {
                    correctAnswers++;
                    //cout << "Great Work!" << endl;
                }
            }
            else
            {
                cout << "      Invalid choice. Please enter 1, 2, or 3." << endl;
                i--; // Repeat the same question
            }
        }

        return (correctAnswers);
    }
    else
    {
        return 404;
    }
}
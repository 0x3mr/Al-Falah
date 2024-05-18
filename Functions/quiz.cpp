#include "../includes.h"

int quiz()
{
    int choi;
    welcome("quiz");

    cin >> choi;

    if (choi == 1)
    {
        int correctAnswers = 0;
        string line, lineChoice, question;
        ifstream file("questions.txt");
        ifstream file2("questions-choices.txt");

        clear();

        if (!file || !file2) {
            cerr << "Error: Unable to open questions.txt or questions-choices.txt file." << endl;
            return (0);
        }

        // Randomize the order of questions
        vector<string> questions, choices;
        while (getline(file, line) && getline(file2, lineChoice))
        {
            questions.push_back(line);
            choices.push_back(lineChoice);
        }
        file.close();
        file2.close();

        random_device rd;
        mt19937 g(rd());
        shuffle(questions.begin(), questions.end(), g);
        shuffle(choices.begin(), choices.end(), g);

        // Display the first 5 questions and get user input
        for (int i = 0; i < 5; i++)
        {
            string question = questions[i];
            string choice = choices[i];
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
                char userAnswer = 'a' + userChoice - 1;
                if (userAnswer == correctAnswer)
                {
                    correctAnswers++;
                    //cout << "Great Work!" << endl;
                }
            }
            else
            {
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
                i--; // Repeat the same question
            }
        }

        return (correctAnswers);
    }
    else
    {
        return 404;
    }
    return (0);
}
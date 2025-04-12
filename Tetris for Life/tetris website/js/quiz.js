document.getElementById('quiz-form').addEventListener('submit', function (e) {
    e.preventDefault();  // prevent the form from submitting

    const result = document.getElementById('result');
    // const submitButton = document.querySelector('.submit-btn');
    let score = 0;

    // get the player's name
    const playerName = document.getElementById('player-name').value;

    // check that all questions have been answered
    const questions = ['solving', 'planning', 'organization', 'adapt', 'decision'];
    let allAnswered = true;

    // check if each question has an answer
    questions.forEach(question => {
        // get the checked radio button with the name matching 'question'
        const answer = document.querySelector(`input[name="${question}"]:checked`);
        if (answer) {
            score += parseInt(answer.value);  // add value to score if answered
        } else {
            allAnswered = false;  // mark as false if no answer is selected
        }
    });

    // if not all questions are answered, prevent form submission and show warning
    if (!allAnswered) {
        alert("Please answer all questions before submitting.");
        return;
    }

    // determine the Tetris block based on score
    let block = '';
    if (score <= 5) {
        block = 'T';
    } else if (score <= 10) {
        block = 'L';
    } else if (score <= 12) {
        block = 'Z';
    } else if (score <= 15) {
        block = 'S';
    } else if (score <= 18) {
        block = 'I';
    } else if (score <= 20) {
        block = 'Square';
    } else if (score <= 25) {  // Added condition for J block
        block = 'J';
    }

    // display the result
    result.innerHTML = `<h2>${playerName}! Your Tetris Block: ${block}</h2>`;
    const blockLink = `../../subpages/activities/quizResult/block${block}.html`;
    result.innerHTML += `<a href="${blockLink}" target="_blank" class="hover-link">View your block</a>`;
});

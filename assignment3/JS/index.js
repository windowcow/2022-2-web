// Get enter button
const enterButton = document.querySelector(".enter");

// Move to Quiz Page
function choiceButtonPress() {
    choiceClicked();
}

// move to another page.
function choiceClicked() {
  window.location.href = "html/quizpage.html";
}

// Add enter button event listener
enterButton.addEventListener("click", choiceButtonPress);
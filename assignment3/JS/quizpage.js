import { quiz1, quiz2, quiz3, quiz4 } from "./quizdata.js";

var questionNum = 0;
var score = 0;
var quizs = [quiz1, quiz2, quiz3, quiz4];
shuffle(quizs);
var currentQuiz = quizs[0];

$(document).ready(function() {
    shuffle(quizs);
    currentQuiz = quizs[0];
    fetch();
    
    $(".quiz").on("click", function() {
        
        
        var choice = $(this).children('.inside-deco').text();
        var answer = currentQuiz.answer;
        if (choice === answer) {
            $(this).css("background-color", "#00ff00");
            $(this).prop("disabled", true);
            setTimeout(right, 1000);
        }
        else {
            $(this).css("background-color", "#ff0000");
            $(this).prop("disabled", true);
            setTimeout(wrong, 1000);
        }
        
        
        
    });
});

// Shuffle
function shuffle(array) {
    array.sort(() => Math.random() - 0.5);
}

function fetch() {
    if (questionNum == 4) {
        localStorage.setItem("resultScore", score);
        window.location.href = "result.html";
    }
    else {
        $(".numerator").text(questionNum + 1);
        $(".score").text(score);
        $(".quiz-title").text(currentQuiz.quiz);
        $(".btn-text").each(function(index) {
            $(this).text(currentQuiz.choices[Object.keys(currentQuiz.choices)[index]]);
        });
    }
}

function right(){
    
    $(".quiz").each(function(index) {
        $(this).css("background-color", "#ffffff");
        $(this).prop("disabled", false);
    });
    score++;
    questionNum++;
    $(".progress-bar").css("width", (questionNum+1) * 25 + "%");
    currentQuiz = quizs[questionNum];
    fetch();

}

function wrong(){
    $(".quiz").each(function(index) {
        $(this).css("background-color", "#ffffff");
        $(this).prop("disabled", false);

    });
    questionNum++;
    $(".progress-bar").css("width", (questionNum+1) * 25 + "%");
    currentQuiz = quizs[questionNum];
    fetch();
}
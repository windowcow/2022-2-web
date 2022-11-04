$(document).ready(function() {
    $(".resultScore").text(localStorage.getItem("resultScore"));
    localStorage.removeItem("resultScore");
    $(".enter").on("click", function() {
        window.location.href = "./quizpage.html";
    });
});


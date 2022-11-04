// Set Quiz
const quiz1 = {
    quiz: "Which one is NOT a legal variable name?",
    choices: {
        a: "_myvar",
        b: "Myvar",
        c: "my_var",
        d: "my-var"
    },
    answer: "D"
};

const quiz2 = {
    quiz: "What is a correct syntax to output 'Hello World' in Python?",
    choices: {
        a: 'print("Hello World");',
        b: 'p("Hello World")',
        c: 'echo("Hello World);',
        d: 'echo "Hello World"'
    },
    answer: "A"
};

const quiz3 = {
    quiz: "How do you insert COMMENTS in Python code?",
    choices: {
        a: "/*This is a comment*/",
        b: "#This is a comment",
        c: "//This is a comment;",
        d: "None of the above;"
    },
    answer: "B"
    
};

const quiz4 = {
    quiz: "What is the correct syntax to output the type of a variable or object in Python?",
    choices: {
        a: "print(typeof(x))",
        b: "print(typeof x)",
        c: "print(typeOf(x))",
        d: "print(type(x))"
    },
    answer: "D"
    
};

export { quiz1, quiz2, quiz3, quiz4 };
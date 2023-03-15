const form = document.getElementById("contact-form");
const successMessage = document.getElementById("success-message");

form.addEventListener("submit", function (event) {
    event.preventDefault();

    const name = form.elements["name"].value;
    form.reset();

    if (name === ''){
        successMessage.innerText = "Thanks for getting in touch!";
        successMessage.style.display = "block";
    } else {
        successMessage.innerText = "Thanks for getting in touch, " + name + "!";
        successMessage.style.display = "block";
    }
});
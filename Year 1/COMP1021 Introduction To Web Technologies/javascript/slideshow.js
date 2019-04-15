function changeIndex(x) {
    showSlide(indexOfSlide += x);
}

function showSlide(x) {
    var slides = document.getElementsByClassName("slides");
    var i = 0;
    
    if(x > slides.length-1) {
        indexOfSlide = 0;
    }
    
    if(x < 0) {
        indexOfSlide = slides.length-1;
    }
    
    for(i;i < slides.length;i++) {
            slides[i].style.display = "none";
        }
    slides[indexOfSlide].style.display = "block";
}

var indexOfSlide = 0;

showSlide(indexOfSlide);

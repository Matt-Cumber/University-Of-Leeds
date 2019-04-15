function getDate() {
   var stringDate;
   
    /*---INTIALISE DATE STRING TO CURRENT DAY---*/
    switch (new Date().getDay()) {
        case 0:
            stringDate = "Sun ";
            break;
        case 1:
            stringDate = "Mon ";
            break;
        case 2:
            stringDate = "Tue ";
            break;
        case 3:
            stringDate = "Wed ";
            break;
        case 4:
            stringDate = "Thu ";
            break;
        case 5:
            stringDate = "Fri ";
            break;
        case 6:
            stringDate = "Sat ";
            break;
    }

    /*---CONCAT THE CURRENT DATE---*/
    var date = new Date();
    var currentDate = date.getDate();
    stringDate = stringDate.concat(currentDate," ");

    /*---CONCAT THE CURRENT MONTH---*/
    switch (new Date().getMonth()) {
        case 0:
            stringDate = stringDate.concat("Jan");
            break;
        case 1:
            stringDate = stringDate.concat("Feb");
            break;
        case 2:
            stringDate = stringDate.concat("Mar");
            break;
        case 3:
            stringDate = stringDate.concat("Apr");
            break;
        case 4:
            stringDate = stringDate.concat("May");
            break;
        case 5:
            stringDate = stringDate.concat("Jun");
            break;
        case 6:
            stringDate = stringDate.concat("Jul");
            break;
        case 7:
            stringDate = stringDate.concat("Aug");
            break;
        case 8:
            stringDate = stringDate.concat("Sep");
            break;
        case 9:
            stringDate = stringDate.concat("Oct");
            break;
        case 10:
            stringDate = stringDate.concat("Nov");
            break;
        case 11:
            stringDate = stringDate.concat("Dec");
            break;
        }
    
    /*---CHANGE INNERHTML OF ELEMENT "Date" TO THE DATE STRING---*/
    var x = document.getElementById("Date").innerHTML = stringDate;
    
}

/*---CALL GET DATE FUNCTION SO DATE APEARS ON LOAD---*/
getDate();


function scrollMeter() {
    var winScroll = document.body.scrollTop || document.documentElement.scrollTop;
    var height = document.documentElement.scrollHeight - document.documentElement.clientHeight;
    var scrolled = (winScroll / height) * 100;
    document.getElementById("Meter").style.width = scrolled + "%";
}

/*---CALL SCROLL METER FUNCTION EVERY TIME USER SCROLLS---*/
window.onscroll = function() {scrollMeter()};


function navBar() {
    var navbar = document.getElementById("navbar");
    
    /*---IF THE NAME OF THE CLASS OF NAV BAR IS NAV CHANGE TO RESPONSIVE---*/
    if (navbar.className === "nav") {
        navbar.className += " responsive";
    }
    
    /*---ELSE CHANGE BACK TO NORMAL---*/
    else {
        navbar.className = "nav";
    }
}
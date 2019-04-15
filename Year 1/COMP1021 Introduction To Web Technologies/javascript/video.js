function videoControl() { 
    var video = document.getElementById("video");
    
    /*---IF THE VIDEO IS PAUSED PLAY INSTEAD---*/
    if (video.paused) { 
        video.play(); 
    }
    
    /*---OTHERWISE PAUSE---*/
    else {
        video.pause();
    }
}
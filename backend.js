//Global
var Score = 1;
var HitmarkerSound = new Audio("hitmarker.wav");
var WowSound = new Audio("wow.wav");
var SWESound = new Audio("SWE.wav");
var run90Sound = new Audio("running90s.wav");
var sanicSound = new Audio("sanic.wav");
var ohbabyTripleSound = new Audio("triple.wav");
var noscopedSound = new Audio("noscoped.wav");
var ohmygodSound = new Audio("ohmygod.wav");

function sleep (time) {
  return new Promise((resolve) => setTimeout(resolve, time));
}

function moveTarget()
{
  //Variables
  var randX = Math.floor(Math.random() * 90);
  var randY = Math.floor(Math.random() * 90);
  var target = document.getElementById('targetButton');
  var scoreBoard = document.getElementById('scoreboard');

  if(Score%5 == 0)
  {
    const wowIMG = document.createElement('img');
    wowIMG.id = "wowIMG"
    wowIMG.src = "wow_t.gif";
    wowIMG.style.cssText = "z-index: -1; margin: 0; position: absolute; top: " + Math.floor(Math.random() * 90) + "%; left: "+ Math.floor(Math.random() * 90) +"%; cursor: url('hitmarker_g.png') 16 16, auto;";
    document.body.appendChild(wowIMG);
    WowSound.play();

    sleep(3000).then(() => {
    wowIMG.remove();
  });
}
   if(Score%5 == 2)
  {
    const snoopIMG = document.createElement('img');
    snoopIMG.id = "snoopIMG"
    snoopIMG.src = "snoopGIF_t.gif";
    snoopIMG.style.cssText = "z-index: -1; margin: 0; position: absolute; top: " + Math.floor(Math.random() * 90) + "%; left: "+ Math.floor(Math.random() * 90) +"%; cursor: url('hitmarker_g.png') 16 16, auto;";
    document.body.appendChild(snoopIMG);
    SWESound.play();

    sleep(3000).then(() => {
      snoopIMG.remove();
  });
}

if(Score%10 == 4)
{
  const mlgfrogIMG = document.createElement('img');
  mlgfrogIMG.id = "mlgfrogIMG"
  mlgfrogIMG.src = "mlgfrog.gif";
  mlgfrogIMG.style.cssText = "z-index: -1; margin: 0; position: absolute; top: " + Math.floor(Math.random() * 90) + "%; left: "+ Math.floor(Math.random() * 90) +"%; cursor: url('hitmarker_g.png') 16 16, auto;";
  document.body.appendChild(mlgfrogIMG);
  run90Sound.play();

  sleep(3000).then(() => {
    mlgfrogIMG.remove();
});
}

  if(Score%10 == 9)
  {
    const sanicIMG = document.createElement('img');
    sanicIMG.id = "sanicIMG"
    sanicIMG.src = "sanic.png";
    sanicIMG.style.cssText = "width:400px; height:400px; z-index: -1; margin: 0; position: absolute; top: " + Math.floor(Math.random() * 70) + "%; left: "+ 0 +"%; cursor: url('hitmarker_g.png') 16 16, auto;";
    document.body.appendChild(sanicIMG);
    sanicSound.play();

    let start = Date.now(); // remember start time

  let timer = setInterval(function() {
  // how much time passed from the start?
  let timePassed = Date.now() - start;

  if (timePassed >= 4000) {
    clearInterval(timer); // finish the animation after 2 seconds
    return;
  }

  // draw the animation at the moment timePassed
  sanicIMG.style.left = timePassed / 2 + 'px';

}, 20);


    sleep(4000).then(() => {
      sanicIMG.remove();
  });

  }

  if(Score%15 == 1)
  {
    noscopedSound.play();

  }
  if(Score%15 == 6)
  {
    ohbabyTripleSound.play();

  }
  if(Score%15 == 11)
  {
    ohmygodSound.play();
  }

  //Text Update
  scoreBoard.textContent = 'Score : ' + Score;
  target.style.cssText = "margin: 0; position: absolute; top: " + randX + "%; left: "+ randY +"%; cursor: url('hitmarker_g.png') 16 16, auto;";

  //Score Update
  Score = Score + 1;



  //Audio
  HitmarkerSound.play();
}



  // background-repeat:no-repeat; background-size:cover;
  const buttons = document.getElementsByClassName('tbPos1');
  
  for (const button of buttons) {
    button.addEventListener('click', moveTarget);
    button.addEventListener('contextmenu', moveTarget);
  }
  
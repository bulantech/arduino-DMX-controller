"use strict";var width=window.innerWidth||document.documentElement.clientWidth||document.body.clientWidth;var isMobile=(width<970?true:false);if(typeof isDeskAd==='undefined')
var isDeskAd=[0,1,0];if(typeof isMobileAd==='undefined')
var isMobileAd=[0,0,0];if(typeof isStickyAd==='undefined')
var isStickyAd=true;if(typeof isAPS==='undefined')
var isAPS=true;if(typeof isLazyAd==='undefined')
var isLazyAd=true;if(typeof topAdSizes==='undefined')
var topAdSizes=(isMobile?[[320,50]]:[[728,90]]);if(typeof rightAdSizes==='undefined')
var rightAdSizes=[[300,600],[160,600],[300,250]];if(typeof bottomAdSizes==='undefined')
var bottomAdSizes=[[320,100],[300,250]];var apstag;var addiv=["div-gpt-ad-1639638001114-0","div-gpt-ad-1631210698489-0","div-gpt-ad-1631993686440-0"];var isFF=navigator.userAgent.indexOf("Firefox")!=-1;var mobileAdsNum=isMobileAd[0]+isMobileAd[1]+isMobileAd[2];var deskAdsNum=isDeskAd[0]+isDeskAd[1]+isDeskAd[2];var adsNum=(isMobile?mobileAdsNum:deskAdsNum);var isAd=(isMobile?isMobileAd:isDeskAd);window.ga=window.ga||function(){(ga.q=ga.q||[]).push(arguments)};ga.l=+new Date;loadScripts();if(document.readyState!=='loading')
tagmngMain();else{window.addEventListener("DOMContentLoaded",function(){tagmngMain();});}
function tagmngMain()
{if(adsNum<3)
hideAdDiv();if(adsNum){if(isMobile&&!isAd[0]){window.addEventListener('scroll',setAds,{once:true});}
else{setAds();if(isStickyAd)setSticky(2);}}
setAnalytics();}
function hideAdDiv()
{for(var i=0;i<isAd.length;i++)
if(!isAd[i]){var el=document.getElementById(addiv[i]);if(el!=null)
el.style.display="none";}}
function loadScripts()
{var ga;if(adsNum)loadGPTScript();ga=document.createElement("script");ga.type="text/javascript";ga.async=true;ga.src="https://www.google-analytics.com/analytics.js";document.head.appendChild(ga);}
function loadGPTScript()
{var ga=document.createElement("script");ga.type="text/javascript";ga.async=true;ga.src="https://securepubads.g.doubleclick.net/tag/js/gpt.js";document.head.appendChild(ga);}
function setAnalytics()
{ga('create','UA-2665076-2','auto');ga('send','pageview');}
function setAds()
{window.googletag=window.googletag||{cmd:[]};googletag.cmd.push(function(){if(isAd[0])
googletag.defineSlot('/22558647090/rapidtables_top_fixed',topAdSizes,addiv[0]).addService(googletag.pubads());if(isAd[1])
googletag.defineSlot('/22558647090/rapidtables_right_fixed',rightAdSizes,addiv[1]).addService(googletag.pubads());if(isAd[2])
googletag.defineSlot('/22558647090/rapidtables_bottom_fixed',bottomAdSizes,addiv[2]).addService(googletag.pubads());if(isAPS&&!isFF)
googletag.pubads().disableInitialLoad();if(isAd[2]&&isLazyAd){googletag.pubads().enableLazyLoad({fetchMarginPercent:80,renderMarginPercent:40,mobileScaling:1.0});}
googletag.pubads().enableSingleRequest();googletag.enableServices();});if(isAPS&&!isFF)
initAPS();for(var i=0;i<isAd.length;i++)
if(isAd[i]){googletag.cmd.push(function(){googletag.display(addiv[i]);});break;}}
function setSticky(nh)
{if(isMobile)return;var wrap=document.getElementById("wrapper");var rcol=document.getElementById("rcol");rcol.setAttribute("style","position:sticky; top:0;");var h=window.innerHeight||document.documentElement.clientHeight||document.body.clientHeight;var hwrap=wrap.getBoundingClientRect().height;var hrcol=rcol.getBoundingClientRect().height;var dh=(hwrap-hrcol)-nh*h;if(dh<0){hwrap-=dh;wrap.style.height=hwrap+"px";}
else{hrcol+=dh;rcol.style.height=hrcol+"px";}}
function initAPS()
{!function(a9,a,p,s,t,A,g){if(a[a9])return;function q(c,r){a[a9]._Q.push([c,r])}a[a9]={init:function(){q("i",arguments)},fetchBids:function(){q("f",arguments)},setDisplayBids:function(){},targetingKeys:function(){return[]},_Q:[]};A=p.createElement(s);A.async=!0;A.src=t;g=p.getElementsByTagName(s)[0];g.parentNode.insertBefore(A,g)}("apstag",window,document,"script","//c.amazon-adsystem.com/aax2/apstag.js");apstag.init({pubID:'f48dc2f5-feda-43b9-a3bf-8d668de2484f',adServer:'googletag'});var slot=[];var islot=0;if(isAd[0]){slot[islot++]={slotID:addiv[0],slotName:'/22558647090/rapidtables_top_fixed',sizes:topAdSizes};}
if(isAd[1]){slot[islot++]={slotID:addiv[1],slotName:'/22558647090/rapidtables_right_fixed',sizes:rightAdSizes};}
if(isAd[2]){slot[islot]={slotID:addiv[2],slotName:'/22558647090/rapidtables_bottom_fixed',sizes:bottomAdSizes};}
apstag.fetchBids({slots:slot,timeout:2e3},function(bids){googletag.cmd.push(function(){apstag.setDisplayBids();googletag.pubads().refresh();});});}
function initShare()
{if(document.getElementById("sharefb")!=null)
{document.getElementById("sharefb").href="https://facebook.com/sharer/sharer.php?u="+encodeURIComponent(window.location.href)+"&title="+encodeURIComponent(document.title);document.getElementById("sharetw").href="https://twitter.com/intent/tweet?text="+encodeURIComponent(document.title)+"&url="+encodeURIComponent(window.location.href);document.getElementById("sharewa").href="https://wa.me/?text="+encodeURIComponent(document.title)+" "+encodeURIComponent(window.location.href);document.getElementById("shareml").href="mailto:?to=&subject="+encodeURIComponent(document.title)+"&body="+encodeURIComponent(window.location.href);}}
function OnSubFb()
{var m="feedback.";var txt=document.getElementById("fdbkarea").value;var url=window.location.href;var body="Page URL:\r\n"+url;body+="\r\nScreen size:\r\n"+window.screen.width+"x"+window.screen.height;body+="\r\nOS:\r\n"+window.navigator.platform;body+="\r\nUser agent:\r\n"+window.navigator.userAgent;body+="\r\n\r\nMessage:\r\n"+txt;body=encodeURIComponent(body);m+="rapidtables@gmail.com";var href="mailto:"+m+"?subject=Page%20Feedback&body="+body;if(txt.length>30)
{var form=document.getElementById("fdbkform");function handleForm(e){e.preventDefault();}form.addEventListener('submit',handleForm);window.location.href=href;document.getElementById("fdbkmsg").textContent="If your mail client is not defined, please copy & send your message to "+m;}}
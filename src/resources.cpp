/*Balance of Power: Reviewed: A complex turn-based geopolitical simulation game
* Copyright (c) 2016 Tomasz Ciborski (author of the port)
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "resources.h"

void Resources::setStrings(){

    strg[0]="Spheres of influence";
    strg[1]="Major events";
    strg[2]="Prestige value";
    strg[3]="Insurgency";
    strg[4]="Likelihood of coup d'etat";
    strg[5]="Likelihood of finlandization to the USA";
    strg[6]="Likelihood of finlandization to the USSR";
    strg[7]="Countries at war";

    strg[8]="Diplomatic relations of ";
    strg[9]="Diplomatic attitude towards ";
    strg[10]="Military aid sent by ";
    strg[11]="Military aid sent into ";
    strg[12]="Insurgency aid sent by ";
    strg[13]="Insurgency aid sent to ";
    strg[14]="Troops for govt sent by ";
    strg[15]="Troops for govt sent into ";
    strg[16]="Troops for rebels sent by ";
    strg[17]="Troops for rebels sent into ";
    strg[18]="Economic aid sent by ";
    strg[19]="Economic aid sent to ";
    strg[20]="Destabilization efforts by";
    strg[21]="Destabilization efforts towards ";
    strg[22]="Pressure applied by ";
    strg[23]="Pressure applied towards ";
    strg[24]="Treaty relationships with ";
    strg[25]="Treaty relationships with ";
    strg[26]="Trade policies of ";
    strg[27]="Trade policies of ";

    strg[28]="Hover on a country for more details\nor click on it to switch the view";

    strg[29]="Military conflicts with ";

    strg[33]="GDP";
    strg[34]="Consumer spending";
    strg[35]="Investment spending";
    strg[36]="Military spending";
    strg[37]="Population";
    strg[38]="Military personnel";
    strg[39]="Literacy rate";
    strg[40]="Energy production";
    strg[41]="Calories intake";
    strg[42]="Doctors per capita";
    strg[43]="Infant mortality";
    strg[44]="School enrollment";
    strg[45]="TV sets per capita";
    strg[46]="Telephones per capita";
    strg[47]="Protests";
    strg[48]="Violent political deaths";
    strg[49]="Riots";
    strg[50]="Armed attacks";
    strg[51]="Assasinations";
    strg[52]="Executions";
    strg[53]="Political rights";
    strg[54]="Civil rights";
    strg[55]="Agriculture share";
    strg[56]="Industry share";
    strg[57]="Services share";
    strg[58]="Trade share";
    strg[59]="Taxation share";
    strg[60]="Public education share";
    strg[61]="Public healthcare share";
    strg[62]=" per capita";
    strg[63]=" per GDP";

    //relationships
    strg[64]="Enemy";
    strg[65]="Hostile";
    strg[66]="Cold";
    strg[67]="Cool";
    strg[68]="Neutral";
    strg[69]="Cordial";
    strg[70]="Friendly";
    strg[71]="Warm";
    strg[72]="Close";

    //milAid/insgAid
    strg[73]="$0 million";
    strg[74]="$20 million";
    strg[75]="$100 million";
    strg[76]="$400 million";
    strg[77]="$1 billion";
    strg[78]="$2 billion";

    //intervention
    strg[79]="0 men";
    strg[80]="1,000 men";
    strg[81]="5,000 men";
    strg[82]="20,000 men";
    strg[83]="100,000 men";
    strg[84]="500,000 men";

    //econAid
    strg[85]="$0 million";
    strg[86]="$200 million";
    strg[87]="$400 million";
    strg[88]="$1 billion";
    strg[89]="$2 billion";
    strg[90]="$4 billion";

    //destabil
    strg[91]="No activity";
    strg[92]="Help dissidents";
    strg[93]="Fund opposition";
    strg[94]="Incite riots";
    strg[95]="Assassinations";
    strg[96]="Support coup";

    //pressure
    strg[697]="None";
    strg[698]="Quiet diplomacy";
    strg[699]="Public posturing";
    strg[700]="Moderate pressure";
    strg[701]="Intense pressure";
    strg[702]="Diplomatic offensive";

    //treaty
    strg[102]="No relations";
    strg[103]="Diplomatic relations";
    strg[104]="Trade relations";
    strg[105]="Military bases";
    strg[106]="Conventional defense";
    strg[107]="Nuclear defense";

    //finland
    strg[108]="Invulnerable";
    strg[109]="Low";
    strg[110]="Moderate";
    strg[111]="High";
    strg[112]="Very high";

    //insurgency
    strg[113]="Civil war";
    strg[114]="Major guerilla war";
    strg[115]="Minor guerilla war";
    strg[116]="Rampant terrorism";
    strg[117]="Minor terrorism";
    strg[118]="Slight unrest";
    strg[119]="Peaceful";

    //influence
    strg[120]="Absolutely USSR";
    strg[121]="Strongly USSR";
    strg[122]="Moderately USSR";
    strg[123]="Fairly USSR";
    strg[124]="Slightly USSR";
    strg[125]="Slightly USA";
    strg[126]="Fairly USA";
    strg[127]="Moderately USA";
    strg[128]="Strongly USA";
    strg[129]="Absolutely USA";

    //legends
    strg[130]="Max.";
    strg[131]="Medium";
    strg[132]="Min.";
    strg[133]="War";
    strg[134]="";
    strg[135]="Peace";
    strg[136]="Coup d'etat";
    strg[137]="Revolution";
    strg[138]="Finlandization";
    strg[139]="More friendly";
    strg[140]="Neutral";
    strg[141]="More hostile";
    strg[142]="More USA";
    strg[143]="Neither";
    strg[144]="More USSR";

    //units
    strg[145]="$ ";
    strg[146]=" Ms";
    strg[147]=" k";
    strg[148]=" k men";
    strg[149]="%";
    strg[150]="% of GDP";
    strg[151]="kcal/cap/day";
    strg[152]="per 1,000";

    strg[153]="Click on a country for more details";

    //country names
    strg[154]="United States";
    strg[155]="Soviet Union";
    strg[156]="Mexico";
    strg[157]="Honduras";
    strg[158]="Nicaragua";
    strg[159]="Panama";
    strg[160]="Cuba";
    strg[161]="Argentina";
    strg[162]="Colombia";
    strg[163]="Peru";
    strg[164]="Venezuela";
    strg[165]="Brazil";
    strg[166]="Chile";
    strg[167]="Canada";
    strg[168]="Greece";
    strg[169]="Sweden";
    strg[170]="United Kingdom";
    strg[171]="France";
    strg[172]="Spain";
    strg[173]="West Germany";
    strg[174]="Romania";
    strg[175]="Italy";
    strg[176]="East Germany";
    strg[177]="Poland";
    strg[178]="Czechoslovakia";
    strg[179]="Yugoslavia";
    strg[180]="South Africa";
    strg[181]="Egypt";
    strg[182]="Tunisia";
    strg[183]="Morocco";
    strg[184]="Algeria";
    strg[185]="Libya";
    strg[186]="Mali";
    strg[187]="Nigeria";
    strg[188]="Sudan";
    strg[189]="Ethiopia";
    strg[190]="Kenya";
    strg[191]="Zaire";
    strg[192]="Tanzania";
    strg[193]="Mozambique";
    strg[194]="Zambia";
    strg[195]="Angola";
    strg[196]="Japan";
    strg[197]="North Korea";
    strg[198]="South Korea";
    strg[199]="Australia";
    strg[200]="China";
    strg[201]="Vietnam";
    strg[202]="Turkey";
    strg[203]="Syria";
    strg[204]="Israel";
    strg[205]="Taiwan";
    strg[206]="Iraq";
    strg[207]="Saudi Arabia";
    strg[208]="Iran";
    strg[209]="Afghanistan";
    strg[210]="Pakistan";
    strg[211]="India";
    strg[212]="Burma";
    strg[213]="Thailand";
    strg[214]="Indonesia";
    strg[215]="Philippines";
    strg[216]="Guatemala";
    strg[217]="El Salvador";
    strg[218]="Costa Rica";
    strg[219]="Mauritania";
    strg[220]="Guinea";
    strg[221]="Ivory Coast";
    strg[222]="Burkina Faso";
    strg[223]="Ghana";
    strg[224]="Niger";
    strg[225]="Chad";
    strg[226]="Cameroon";
    strg[227]="Central Africa";
    strg[228]="Congo";
    strg[229]="Zimbabwe";
    strg[230]="Botswana";
    strg[231]="Jordan";
    strg[232]="Lebanon";
    strg[233]="Bolivia";
    //country adjectives
    strg[234]="American";
    strg[235]="Soviet";
    strg[236]="Mexican";
    strg[237]="Honduran";
    strg[238]="Nicaraguan";
    strg[239]="Panamanian";
    strg[240]="Cuban";
    strg[241]="Argentinian";
    strg[242]="Colombian";
    strg[243]="Peruvian";
    strg[244]="Venezuelan";
    strg[245]="Brazilian";
    strg[246]="Chilean";
    strg[247]="Canadian";
    strg[248]="Greek";
    strg[249]="Swedish";
    strg[250]="British";
    strg[251]="French";
    strg[252]="Spainish";
    strg[253]="West German";
    strg[254]="Romanian";
    strg[255]="Italian";
    strg[256]="East German";
    strg[257]="Polish";
    strg[258]="Czechoslovak";
    strg[259]="Yugoslavian";
    strg[260]="South African";
    strg[261]="Egyptian";
    strg[262]="Tunisian";
    strg[263]="Moroccan";
    strg[264]="Algerian";
    strg[265]="Libyan";
    strg[266]="Malian";
    strg[267]="Nigerian";
    strg[268]="Sudanese";
    strg[269]="Ethiopian";
    strg[270]="Kenyan";
    strg[271]="Zairian";
    strg[272]="Tanzanian";
    strg[273]="Mozambican";
    strg[274]="Zambian";
    strg[275]="Angolan";
    strg[276]="Japanese";
    strg[277]="North Korean";
    strg[278]="South Korean";
    strg[279]="Australian";
    strg[280]="Chinese";
    strg[281]="Vietnamese";
    strg[282]="Turkish";
    strg[283]="Syrian";
    strg[284]="Israeli";
    strg[285]="Taiwanese";
    strg[286]="Iraqi";
    strg[287]="Saudi";
    strg[288]="Iranian";
    strg[289]="Afghani";
    strg[290]="Pakistani";
    strg[291]="Indian";
    strg[292]="Burmese";
    strg[293]="Thai";
    strg[294]="Indonesian";
    strg[295]="Filipino";
    strg[296]="Guatemalan";
    strg[297]="Salvadoran";
    strg[298]="Costa Rican";
    strg[299]="Mauritanian";
    strg[300]="Guinean";
    strg[301]="Ivorian";
    strg[302]="Burkinabe";
    strg[303]="Ghanaian";
    strg[304]="Nigerien";
    strg[305]="Chadian";
    strg[306]="Cameroonian";
    strg[307]="Central African";
    strg[308]="Congolese";
    strg[309]="Zimbabwean";
    strg[310]="Botswanan";
    strg[311]="Jordanian";
    strg[312]="Lebanese";
    strg[313]="Bolivian";
    //capitals
    strg[314]="Washington";
    strg[315]="Moscow";
    strg[316]="Mexico City";
    strg[317]="Tegucigalpa";
    strg[318]="Managua";
    strg[319]="Panama City";
    strg[320]="Havana";
    strg[321]="Buenos Aires";
    strg[322]="Bogota";
    strg[323]="Lima";
    strg[324]="Caracas";
    strg[325]="Brasilia";
    strg[326]="Santiago";
    strg[327]="Ottawa";
    strg[328]="Athens";
    strg[329]="Stockholm";
    strg[330]="London";
    strg[331]="Paris";
    strg[332]="Madrid";
    strg[333]="Bonn";
    strg[334]="Bucharest";
    strg[335]="Rome";
    strg[336]="Berlin";
    strg[337]="Warsaw";
    strg[338]="Prague";
    strg[339]="Belgrade";
    strg[340]="Pretoria";
    strg[341]="Cairo";
    strg[342]="Tunis";
    strg[343]="Rabat";
    strg[344]="Algiers";
    strg[345]="Tripoli";
    strg[346]="Bamako";
    strg[347]="Abuja";
    strg[348]="Khartoum";
    strg[349]="Addis Ababa";
    strg[350]="Nairobi";
    strg[351]="Kinshasa";
    strg[352]="Dodoma";
    strg[353]="Maputo";
    strg[354]="Lusaka";
    strg[355]="Luanda";
    strg[356]="Tokyo";
    strg[357]="Pyongyang";
    strg[358]="Seoul";
    strg[359]="Canberra";
    strg[360]="Beijing";
    strg[361]="Hanoi";
    strg[362]="Ankara";
    strg[363]="Damascus";
    strg[364]="Tel Aviv";
    strg[365]="Taipei";
    strg[366]="Baghdad";
    strg[367]="Riyadh";
    strg[368]="Tehran";
    strg[369]="Kabul";
    strg[370]="Islamabad";
    strg[371]="New Delhi";
    strg[372]="Yangoon";
    strg[373]="Bangkok";
    strg[374]="Jakarta";
    strg[375]="Manila";
    strg[376]="Guatemala City";
    strg[377]="Salvador";
    strg[378]="San Jose";
    strg[379]="Nouakchott";
    strg[380]="Conakry";
    strg[381]="Yamoussoukro";
    strg[382]="Ouagadougou";
    strg[383]="Accra";
    strg[384]="Niamey";
    strg[385]="N'Djamena";
    strg[386]="Yaounde";
    strg[387]="Bangui";
    strg[388]="Brazzaville";
    strg[389]="Harare";
    strg[390]="Gaborone";
    strg[391]="Amman";
    strg[392]="Beirut";
    strg[393]="La Paz";



    //Window- close up
    strg[475]="Relationship";
    strg[476]="Prestige Value";
    strg[477]="Military Aid";
    strg[478]="Insurgency Aid";
    strg[479]="Intervene-govt";
    strg[480]="Intervene-rebs";
    strg[481]="Economic Aid";
    strg[482]="Destabilization";
    strg[483]="Pressure";
    strg[484]="Treaty";
    strg[485]="Finlandization?";
    strg[486]="Annual Change";
    //---
    strg[487]="Insurgency";
    strg[488]="Govt Philosophy";
    strg[489]="Military Power";
    strg[490]="Sphere of Influence";
    strg[491]="Govt Stability";
    strg[492]="Capital";
    strg[493]="Leader";
    strg[494]="Insurgency";
    //--
    strg[495]="USA value";
    strg[496]="USSR value";
    strg[497]="Other value";
    strg[498]="Net Sent";

    strg[499]="Extreme left";
    strg[500]="Extreme left";
    strg[501]="Extreme left";
    strg[502]="Far left";
    strg[503]="Very left";
    strg[504]="Left";
    strg[505]="Moderate left";
    strg[506]="Slight left";
    strg[507]="Centrist";
    strg[508]="Slight right";
    strg[509]="Moderate right";
    strg[510]="Right";
    strg[511]="Very right";
    strg[512]="Far right";
    strg[513]="Extreme right";
    strg[514]="Extreme right";
    strg[515]="Extreme right";

    strg[516]="Insignificant";
    strg[517]="Very weak";
    strg[518]="Weak";
    strg[519]="Minor";
    strg[520]="Moderate";
    strg[521]="Strong";
    strg[522]="Very strong";
    strg[523]="Superpower";

    strg[524]="About to fall";
    strg[525]="Very shaky";
    strg[526]="Shaky";
    strg[527]="Weak";
    strg[528]="Fair";
    strg[529]="Stable";
    strg[530]="Strong";
    strg[531]="Very strong";

    strg[532]="Weakening quickly";
    strg[533]="Weakening";
    strg[534]="Weakening slowly";
    strg[535]="Strengthening slowly";
    strg[536]="Strengthening";
    strg[537]="Strengthening quickly";

    strg[538]="Insurgency growing";
    strg[539]="Insurgency weakening";

    strg[540]="President";
    strg[541]="Prime Minister";
    strg[542]="Secretary General";
    strg[543]="King";
    strg[544]="Chancellor";
    strg[545]="Leader";
    strg[546]="Ayatollah";
    strg[547]="Chairman";

    strg[548]="Newspaper";
    strg[549]="USA Actions";
    strg[550]="USA Other";
    strg[551]="USSR Actions";
    strg[552]="USSR Other";
    strg[553]="Minor Country News";

    strg[554]="They will ream us on this one!";
    strg[555]="They've got a lock on this one.";
    strg[556]="Give it up; it's hopeless.";
    strg[557]="Don't touch this one.";
    strg[558]="They've got us cold.";
    strg[559]="Back down.";
    strg[560]="This one is theirs.";
    strg[561]="We've got no case here.";
    strg[562]="Not this time.";
    strg[563]="We can't win this.";
    strg[564]="They won't back down.";
    strg[565]="This is not worth fighting over.";
    strg[566]="I don't think we can win this.";
    strg[567]="This is a fight I'd rather avoid.";
    strg[568]="This is a touch risky.";
    strg[569]="We can go either way here.";
    strg[570]="This is a very close judgement call.";
    strg[571]="Perhaps we should give it a whirl.";
    strg[572]="I think we can win this.";
    strg[573]="Don't be afraid.";
    strg[574]="I think we should go for it.";
    strg[575]="We can win this one.";
    strg[576]="They'll back down.";
    strg[577]="They're out of line here.";
    strg[578]="Stand firm on this.";
    strg[579]="We've got them cold.";
    strg[580]="They really goofed this time.";
    strg[581]="This one is ours.";
    strg[582]="Don't let them get away with this.";
    strg[583]="Jump all over them.";
    strg[584]="Stick it to 'em!";
    strg[585]="Nuke 'em!";

    strg[586]="Destabilization";
    strg[587]="Economic Aid";
    strg[588]="Military Aid";
    strg[589]="Aid to Insurgents";
    strg[590]="Intervene for Govt";
    strg[591]="Intervene for Rebels";
    strg[592]="Diplomatic Pressure";
    strg[593]="Treaty";

    strg[594]="Insurgency";
    strg[595]="Military and Insurgency Aid";
    strg[596]="Military and Insurgency Intervene";
    strg[597]="Government Stability";
    strg[598]="Economic Aid and Destabilization";
    strg[599]="Diplomatic Relationships";
    strg[600]="Finlandization Likelihood";
    strg[601]="Treaties and Diplomatic Pressure";
    strg[602]="Internal Pressure on Security";

    strg[603]="USA pro-govt";
    strg[604]="USSR pro-govt";
    strg[605]="USA anti-govt";
    strg[606]="USSR anti-govt";

    strg[607]="Beginner";
    strg[608]="Intermediate";
    strg[609]="Expert";
    strg[610]="Multipolar";
    strg[611]="USA";
    strg[612]="USSR";
    strg[613]="One player";
    strg[614]="Two players";

    strg[615]="Insignificant";
    strg[616]="Very low";
    strg[617]="Low";
    strg[618]="Moderate";
    strg[619]="Considerable";
    strg[620]="High";
    strg[621]="Very high";
    strg[622]="Utmost";

    strg[623]="Huge decrease";
    strg[624]="Large decrease";
    strg[625]="Moderate decrease";
    strg[626]="Small decrease";
    strg[627]="Tiny decrease";
    strg[628]="Tiny increase";
    strg[629]="Small increase";
    strg[630]="Moderate increase";
    strg[631]="Large increase";
    strg[632]="Huge increase";

    strg[633]="Too late";
    strg[634]="DefCon 1";
    strg[635]="DefCon 2";
    strg[636]="DefCon 3";
    strg[637]="DefCon 4";
    strg[638]="Threaten";
    strg[639]="Refuse";
    strg[640]="Challenge";
    strg[641]="Reject";

    strg[642]="Question";
    strg[643]="Insist";
    strg[644]="Question";
    strg[645]="Protest";
    strg[646]="Question";
    strg[647]="Press";
    strg[648]="Question";
    strg[649]="Implore";
    strg[650]="Question";

    strg[703]="The White House*The American government*The American nation*The USA";
    strg[704]="The Soviet Union*The Soviet government*The Soviet nation*The USSR";

    strg[705]=" requests reconsideration of* deplores* protests* demands reversal of";
    strg[706]=" this action.* this policy.* this activity.* this policy.";

    strg[707]=" will defend* will protect* will fight for* will defend";
    strg[708]=" this principle.* this affair.* this matter.* this policy.";

    strg[709]=" is disappointed with* strongly condemns* will not tolerate* is outraged by";
    strg[710]=" this imperialist* this criminal* this threatening* this irrational";
    strg[711]=" action.* behavior.* aggression.* provocation.";

    strg[712]=" regards* considers* sees* views";
    strg[713]=" this matter as* this policy as* this event as* this action as";
    strg[714]=" a crucial concern.* important to its security.* critical to its security.* totally non-negotiable.";

    strg[715]=" is ready* will not hesitate* may have no other choice than* is ready";
    strg[716]=" * * * ";
    strg[717]="to take*to resort to*to respond with*to execute";
    strg[718]=" unambiguous steps.* strong measures.* decisive action.* our military options.* use of military forces.";

    strg[719]=" will not be intimidated by* will not be threatened by* is not scared by* will not be intimidated by";
    strg[720]=" this abusive rhetoric.* these idle insults.* this irresponsible talk.* these ugly messages.";

    strg[721]=" mobilizes* deploys* increases combat readiness of* strenghtens";
    strg[722]=" its conventional defence systems* its defensive forces* its instant reaction forces* its defensive systems";
    strg[723]=" to deal with this threat.* to deal with this contemptible aggressiveness.* to end this meaningless game.* to deal with this arrogance.";

    strg[724]=" announces* declares* announces* declares";
    strg[725]=" total mobilization of* maximum combat readiness of* maximum alert state of* full deployment of";
    strg[726]=" its armed forces.* its nuclear defense systems.* its military forces.* its military personnel.";
    //-------------
    strg[727]=" understands your* respects your* agrees to your* respects your";
    strg[728]=" diplomatic note.* demands.* statements.* proposals.";

    strg[729]=" did not mean* did not intend* did not wish* had no desire";
    strg[730]=" to threaten* to violate* to intrude upon* to infringe upon";
    strg[731]=" your vital interests.* your concerns.* your sphere of influence.* your interests.";

    strg[732]=" will honor* will respect* understands* agrees to";
    strg[733]=" your proposals.* your demands.* your requests.* your demands.";

    strg[734]=" accepts that this dispute* agrees that this conflict* admits that this misunderstanding* admits that this disagreement";
    strg[735]=" is not vital to* is not a major factor in* does not directly bear on* will not directly affect";
    strg[736]=" its security.* its interests.* its concerns.* its sphere of influence.";

    strg[737]=" will honor* will respect* understands* agrees to";
    strg[738]=" your proposals.* your demands.* your requests.* your demands.";

    strg[739]=" does not want to* would not like to* does not want to* would not like to";
    strg[740]=" escalate* risk the military conflict over* risk the peace between our nations over* worsen relations between our nations over";
    strg[741]=" this matter.* this policy.* this action.* this affair.";

    strg[742]=" will honor* will respect* understands* agrees to";
    strg[743]=" your requests.* your demands.* your requests.* your demands.";

    strg[744]=" does not want to* would not like to* does not want to* would not like to";
    strg[745]=" escalate* risk the nuclear conflict over* risk the world peace over* risk the peace between our nations over";
    strg[746]=" this matter.* this policy.* this action.* this affair.";
    //------------
    //------------
    strg[842]="Our leaders*We*Our leaders*We";
    strg[843]=" will retain* have decided to preserve* will stand by* will retain";
    strg[844]=" this* our* this* our";
    strg[845]=" policy.* action.* decision.* policy.";

    strg[846]="Our leaders*We*Our leaders*We";
    strg[847]=" will not abandon* do not regret* will not yield on* will not revoke";
    strg[848]=" this* our* this* our";
    strg[849]=" policy.* action.* decision.* policy.";

    strg[850]="This policy*Our action*Our decision*This action";
    strg[851]=" is not subject to* does not defer to* will not be deterred by* is immune to";
    strg[852]=" your* superpower* your* foreign";
    strg[853]=" whims.* pressures.* objections.* objections.";

    strg[854]="We*We*We*We";
    strg[855]=" will not* shall not* will not* shall not";
    strg[856]=" yield to* acquiesce to* defer to* submit to";
    strg[857]=" your objection.* your insistence.* your demands.* your importunations.";

    strg[858]="We*We*We*We";
    strg[859]=" will not* shall not* will not* shall not";
    strg[860]=" yield to* acquiesce to* defer to* submit to";
    strg[861]=" your objection.* your insistence.* your demands.* your importunations.";
    //--
    strg[862]="We*We*We*We";
    strg[863]=" acquiesce* acquiesce* acquiesce* acquiesce";
    strg[864]=" to your* to your* to your* to your";
    strg[865]=" objection.* objection.* objection.* objection.";
    //--
    strg[866]="The White House*The American government*The American nation*The USA";
    strg[867]="The Soviet Union*The Soviet government*The Soviet nation*The USSR";
    strg[868]=" decides not to* would not like to* does not want to* decides not to";
    strg[869]="  escalate* cause mutual reluctance over* cause diplomatic difficulties over* worsen relationships over";
    strg[870]=" this matter.* this issue.* this policy.* this action.";
    //---------------

    //Rebel groups

    //left-wing rebels
    rebels[0][0]="Democratic Party";
        rebels[0][1]="Communist Party";
        rebels[0][2]="insurgency";
        rebels[0][3]="Morazanist";
        rebels[0][4]="Sandinista";
        rebels[0][5]="insurgency";
        rebels[0][6]="26th of July Movement";
        rebels[0][7]="Peronist";
        rebels[0][8]="FARC";
        rebels[0][9]="Shining Path";
        rebels[0][10]="insurgency";
        rebels[0][11]="insurgency";
        rebels[0][12]="MRPF";
        rebels[0][13]="Quebecois";
        rebels[0][14]="17-N Movement";
        rebels[0][15]="insurgency";
        rebels[0][16]="IRA";
        rebels[0][17]="Action directe";
        rebels[0][18]="ETA";
        rebels[0][19]="Red Army Faction";
        rebels[0][20]="Communist Party";
        rebels[0][21]="Red Brigades";
        rebels[0][22]="Communist Party";
        rebels[0][23]="Communist Party";
        rebels[0][24]="Communist Party";
        rebels[0][25]="insurgency";
        rebels[0][26]="African National Congress";
        rebels[0][27]="insurgency";
        rebels[0][28]="insurgency";
        rebels[0][29]="Polisario Front";
        rebels[0][30]="Kabylian";
        rebels[0][31]="Gaddafist";
        rebels[0][32]="Tuareg";
        rebels[0][33]="insurgency";
        rebels[0][34]="SSU";
        rebels[0][35]="Derg";
        rebels[0][36]="insurgency";
        rebels[0][37]="FNLC";
        rebels[0][38]="insurgency";
        rebels[0][39]="FRELIMO";
        rebels[0][40]="UNIP";
        rebels[0][41]="MPLA";
        rebels[0][42]="Red Army";
        rebels[0][43]="People's Army";
        rebels[0][44]="Communist Party";
        rebels[0][45]="Aborigine Liberation Front";
        rebels[0][46]="Communist Party";
        rebels[0][47]="Viet Minh";
        rebels[0][48]="insurgency";
        rebels[0][49]="Ba'ath loyalist";
        rebels[0][50]="PLO";
        rebels[0][51]="Communist Party";
        rebels[0][52]="Ba'ath loyalist";
        rebels[0][53]="insurgency";
        rebels[0][54]="Fedai";
        rebels[0][55]="PDPA";
        rebels[0][56]="Pashtun";
        rebels[0][57]="Sikh movement";
        rebels[0][58]="Kachin";
        rebels[0][59]="Barisan";
        rebels[0][60]="Communist Party";
        rebels[0][61]="New People's Army";
        rebels[0][62]="URNG";
        rebels[0][63]="FMLN";
        rebels[0][64]="insurgency";
        rebels[0][65]="insurgency";
        rebels[0][66]="insurgency";
        rebels[0][67]="insurgency";
        rebels[0][68]="insurgency";
        rebels[0][69]="insurgency";
        rebels[0][70]="insurgency";
        rebels[0][71]="FROLINAT";
        rebels[0][72]="insurgency";
        rebels[0][73]="insurgency";
        rebels[0][74]="insurgency";
        rebels[0][75]="ZANLA";
        rebels[0][76]="insurgency";
        rebels[0][77]="insurgency";
        rebels[0][78]="Hezbollah";
        rebels[0][79]="FALZW";

        //right-wing rebels
        rebels[1][0]="Republican Party";
        rebels[1][1]="Human rights activist";
        rebels[1][2]="insurgency";
        rebels[1][3]="insurgency";
        rebels[1][4]="Contras";
        rebels[1][5]="insurgency";
        rebels[1][6]="insurgency";
        rebels[1][7]="Argentinian";
        rebels[1][8]="AUC";
        rebels[1][9]="insurgency";
        rebels[1][10]="insurgency";
        rebels[1][11]="insurgency";
        rebels[1][12]="insurgency";
        rebels[1][13]="insurgency";
        rebels[1][14]="insurgency";
        rebels[1][15]="insurgency";
        rebels[1][16]="insurgency";
        rebels[1][17]="insurgency";
        rebels[1][18]="insurgency";
        rebels[1][19]="insurgency";
        rebels[1][20]="counter-revolutionary";
        rebels[1][21]="Italian";
        rebels[1][22]="insurgency";
        rebels[1][23]="Solidarity";
        rebels[1][24]="insurgency";
        rebels[1][25]="Bosnian insurgency";
        rebels[1][26]="Afrikaner Resistance Movement";
        rebels[1][27]="Muslim Brotherhood";
        rebels[1][28]="insurgency";
        rebels[1][29]="insurgency";
        rebels[1][30]="insurgency";
        rebels[1][31]="insurgency";
        rebels[1][32]="insurgency";
        rebels[1][33]="insurgency";
        rebels[1][34]="Muslim Brotherhood";
        rebels[1][35]="EDP";
        rebels[1][36]="insurgency";
        rebels[1][37]="insurgency";
        rebels[1][38]="insurgency";
        rebels[1][39]="RENAMO";
        rebels[1][40]="insurgency";
        rebels[1][41]="UNITA";
        rebels[1][42]="insurgency";
        rebels[1][43]="insurgency";
        rebels[1][44]="insurgency";
        rebels[1][45]="Black Koala Movement";
        rebels[1][46]="counter-revolutionary";
        rebels[1][47]="insurgency";
        rebels[1][48]="insurgency";
        rebels[1][49]="Sunni fundamentalist";
        rebels[1][50]="insurgency";
        rebels[1][51]="Kuomintang";
        rebels[1][52]="Sunni fundamentalist";
        rebels[1][53]="Sunni fundamentalist";
        rebels[1][54]="Jundallah";
        rebels[1][55]="Mujahideen";
        rebels[1][56]="Jundallah";
        rebels[1][57]="insurgency";
        rebels[1][58]="insurgency";
        rebels[1][59]="insurgency";
        rebels[1][60]="insurgency";
        rebels[1][61]="insurgency";
        rebels[1][62]="insurgency";
        rebels[1][63]="insurgency";
        rebels[1][64]="insurgency";
        rebels[1][65]="insurgency";
        rebels[1][66]="insurgency";
        rebels[1][67]="insurgency";
        rebels[1][68]="insurgency";
        rebels[1][69]="insurgency";
        rebels[1][70]="insurgency";
        rebels[1][71]="insurgency";
        rebels[1][72]="insurgency";
        rebels[1][73]="CRNM";
        rebels[1][74]="insurgency";
        rebels[1][75]="insurgency";
        rebels[1][76]="insurgency";
        rebels[1][77]="Islamic Action Front";
        rebels[1][78]="Amal Community";
        rebels[1][79]="insurgency";

        //event generator strings
        //-------------------------------
        evnt[0]="0*% troops*% fighters*% soldiers*% troops";
        evnt[1]="0* take control over @.* take control over the capital city.* march victoriously into @.* captured the last regime's stronghold.";
        evnt[2]="0*\nA new revolutionary government is proclaimed by {.*\nNewly appointed = & { seizes power in the country.*\n{ appointed as a new &*\n['s cabinet falls apart";

        evnt[3]="0*> + }*> +*govenment's spokesman*^";
        evnt[4]="0* promises* pledges* announces* vows";
        evnt[5]="0* better relations with* closer ties with* edges closer to* better relations with";
        evnt[6]="0* @.* the _.* the = nation.* the _.";

        evnt[7]="0*End of _-! conflict*Peace treaty signed with _*End of _-! war*Peace between _ and !";
        evnt[8]="0* > forces surrender.* > troops surrender*.^ taken by = troops.* last > troops surrender.";
        evnt[9]="0*\n} leads new pro-_ government*\n} appointed as new +*\n> + } seizes power after post-war shuffles*\n} as a new + of !";

        evnt[10]="0*> + }*minister of defence*government's spokesman*> + }";
        evnt[11]="0* on _-! war:* on _-! conflict:* on war with _:* on _-! war:";
        evnt[12]="0*\n'We will protect our cause'*\n'We had no other way'*\n'We will defend our people'*\n'We are sure about our victory'";

        evnt[13]="1* *Group of army radicals depose and execute & [.*Army officials capture and imprison & [.*Army officials force & [ to leave the office.*& [ resigned from office after snap election.";
        evnt[14]="1* *\nGeneral {*\nGeneral {*\nGeneral {*\nFormer opposition leader {";
        evnt[15]="0* appointed as new &.* forms a new cabinet.* promises rapid reforms.* calls for national unity.";

        evnt[16]="0*= & {*= government*government's spokesman*director of intelligence";
        evnt[17]="0* accuses ! of* blames ! for* presents evidence that ! is* proves that ! is";
        evnt[18]="1* doing nothing.* helping dissidents.* funding the opposition.* inciting riots.* encouraging assassinations.* plotting a coup.";

        evnt[19]="0*> aid package to _*Foreign aid from !*> economic assistance for _*! grants and credits to _";
        evnt[20]="0* upped to* increased to* totals* tops*";
        evnt[21]="1* nothing.* $200 million.* $400 million.* $1 billion.* $2 billion.* $4 billion.";

        evnt[22]="0*!*^*> government*> + }";
        evnt[23]="0* slashes* announces cuts in* reduces* trims*";
        evnt[24]="0* aid for _ to* economic assistance for _ to* aid package for _ to* foreign aid for _ to";
        evnt[25]="1* nothing.* $200 million.* $400 million.* $1 billion.* $2 billion.* $4 billion.";

        evnt[26]="0*!*^*> government*> + }";
        evnt[27]="0* cites diplomatic factors* claims deteriorating relations* refers to 'diplomatic difficulties'* angry with _";
        evnt[28]="0*, rejects = aid package.*, spurns economic aid from _.*, refuses part of = economic aid.*, returns part of = aid.";

        evnt[29]="0*!*^*> government*> + }";
        evnt[30]="0* provides _* offers _* rushes _* gives _";
        evnt[31]="1* nothing* $20 million* $100 million* $400 million* $1 billion* $2 billion";
        evnt[32]="0* in weapons package.* worth of military hardware.* in military aid.* > weapons outlays.";

        evnt[33]="0*> military aid to _*Military aid from ! to _*> military assistance for _*> weapons outlays for _";
        evnt[34]="0* decreased to* declines to* trimmed to* slashed to";
        evnt[35]="1* nothing.* $20 million.* $100 million.* $400 million.* $1 billion.* $2 billion.";

        evnt[36]="0*!*^*> government*> + }";
        evnt[37]="0* declares* maintains* announces* reports";
        evnt[38]="0* '! cannot accept'* refusal of* rejection of* '! will not take'";
        evnt[39]="0* full complement of = military equipment.* entire package of = military assistance.* complete = weapons aid.* all weapons offered by _";

        evnt[40]="0*= & {*Government's spokesman*@*_";
        evnt[41]="0* accuses ! of* castigates ! for* complains that ! is* presents evidence that ! is";
        evnt[42]="1* harboring* assisting* supporting* shipping weapons to* bankrolling* providing massive assistance to";
        evnt[43]="0* % elements.* fighters in the %.* the % underground.* the %.";

        evnt[44]="0*> government*> + }*^*!";
        evnt[45]="0* agrees to* promises to* vows to* accepts plan to";
        evnt[46]="1* eliminate* slash* roll back* cut* reduce* curtail";
        evnt[47]="0* aid to the = %.* funds for the = %.* assistance to the = %.* weapons shipments to the = %.";

        evnt[48]="0*!*^*> + }*> government";
        evnt[49]="0* dispatches* sends* rushes* commits";
        evnt[50]="1* nobody* military advisors* first combat troops* several military units* large military forces* massive military power";
        evnt[51]="0* in support of = government.* to help = government.* at request of = & {.* to assist = regime.";

        evnt[52]="0*> troops*> military forces*> soldiers*> combat forces";
        evnt[53]="0* in _* supporting = regime*  stationed in _* based in _";
        evnt[54]="1* pulled out.* greatly reduced.* scaled down.* cut.* reduced.* trimmed.";

        evnt[55]="1*Last = military personnel*Last = military personnel*Most = troops*Many = soldiers*Some military forces from _";
        evnt[56]="0* ejected* thrown out* forced home* asked to leave";
        evnt[57]="0* by !.* by > +.* by ^* by > government.";

        evnt[58]="1*Nobody*Military advisors*Combat troops*Military units*Large military forces*Massive military forces";
        evnt[59]="0* from !* sent by > +* dispatched by ^* from !";
        evnt[60]="0* intervene in support of rebels* invade = territory for rebels* attack = army units* enter = territory in support of rebels";
        evnt[61]="0* in local conflict.* in civil war.* in = civil war.* in = war.";

        evnt[62]="0*!*> + }*^*> government";
        evnt[63]="0* pulls out* recalls* brings home* disengages";
        evnt[64]="1* all > troops* all but military advisors* most > forces* many > troops* half of invading force";
        evnt[65]="0* from _.* from = war.* from = territory.* from _.";

        evnt[66]="0*!*> + }*+ } of !*> foreign affairs minister";
        evnt[67]="1* does nothing* consults with* publicly condemns* calls on other nations to condemn* pressures* exerts intense pressure on* wages diplomatic offensive against";
        evnt[68]="0* = government.* government of _.* _.* @.";

        evnt[69]="0*= & {* & { of _*_*_";
        evnt[70]="0* inks* signs* consludes* agrees to";
        evnt[71]="1* no treaty* diplomatic relations concord* trade agreement* military bases concord* mutual defense pact* 'total defense' agreement";
        evnt[72]="0* with !.* with + } of !.* with !.* with > +.";

        evnt[73]="0*!*> + }*> foreign minister*> representative";
        evnt[74]="0* cancels* tears up* voids* terminates";
        evnt[75]="4* all relations* diplomatic relations agreement* trade pact* military bases treaty* mutal defense concord* nuclear defense treaty";
        evnt[76]="0* with _.* with = government.* with _.* with = government.";

        evnt[77]="0*Angry > + }*> government*!*^";
        evnt[78]="0* cancels* voids* kills* terminates";
        evnt[79]="4* nothing* diplomatic relations treaty* trade agreement* military bases* concord* mutual defense concord* nuclear defense treaty";
        evnt[80]="0* with _.* with _.* with = government.* with = government.";

        evnt[81]="0*= & {*= government*government's spokesman*director of intelligence";
        evnt[82]="0* reports that* announces that* reports that* announces that";
        evnt[83]="0* > destabilization activities have decreased.* > destabilization activities have decreased.* > destabilization activities have decreased.* > destabilization activities have decreased.";

        evnt[84]="0*!*> + }*+ } of !*!";
        evnt[85]="0* reduces diplomatic pressure on _.* reduces diplomatic pressure on _.* reduces diplomatic pressure on _.* reduces diplomatic pressure on _.";
}

function validateAnalysisType(){
	var x=document.getElementsByName('CheckBoxAnalysisType');
	var count=0;
	for(i=0;i<x.length;i++){
		if(x[i].checked){
			count++;
		};
	};
	if(count == 0 ){
		setLegend("At least one analysis type should be checked.");
		return false;
	};
};

function setLegend(msg){
	var a=document.getElementsByName("legend");
	a[0].textContent= msg;
	a[0].style.color="red";
	a[0].style.fontWeight="bold";
	a[0].focus();
}

function validateData(name,exp){
	var ploidy=document.getElementsByName("SelectPloidy");
	var data=document.getElementsByName(name);
	var lines=data[0].value.split("\n");
	var expected=exp;
	var lineidx=0;
	for(i=0;i<lines.length;i++){
		
		var fileds=lines[i].trim().split(/[\s,]+/);
		if(fileds.length==1 && fileds[0]==""){
			continue;
		}
		if(fileds.length==1){
			setLegend("Error in "+(name=="TextareaCasedata"?"case data":"control data")+", line "+(i+1)+", Only sample ID found. No genotype data given.");
			return false;
		};
		if(expected==0&&lineidx==0){
			if((fileds.length-1)%ploidy[0].value != 0){
				setLegend("Error in "+(name=="TextareaCasedata"?"case data":"control data")+", line "+ (i+1)+ ", Either the snp number or ploidy number is wrong.");
				return false;
			}else
			{
				expected=fileds.length;
			};
		}else
		{
			if(fileds.length!=expected)
			{
				setLegend("Error in "+(name=="TextareaCasedata"?"case data":"control data")+", line "+(i+1)+". Column number is not the same as that in the "+(exp==0?"first line.":"case data."));
				return false;
			};
		};
		lineidx++;
	};
	if(lineidx==0)
	{
		setLegend("Error in "+(name=="TextareaCasedata"?"case data":"control data")+". No data available.");
	return false;
	}
	return expected;

};
			 
function validateForm(){
//return ( validateAnalysisType()&&validateData("TextareaCasedata")&&validateData("TextareaControldata"));
if(validateAnalysisType() == false){
return false;
};
var ret=validateData("TextareaCasedata",0);
if(ret==false){
return false;
};
if(validateData("TextareaControldata",ret)==false){
return false;
}
};

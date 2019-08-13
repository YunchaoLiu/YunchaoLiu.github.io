var file_;
var stage_ ;

//representatation variable
var repr_ball_stick_;
var repr_line_;
var repr_surface_;


//load file
function load_file(file, callback){
	file_ = file;
	document.addEventListener("DOMContentLoaded", function () {
		stage_ = new NGL.Stage("viewport");
		stage_.loadFile(file_).then(function (o) {
		  repr_ball_stick_ = o.addRepresentation("ball+stick");
		  repr_line_ = o.addRepresentation("line");
		  repr_surface_ = o.addRepresentation("surface");

		  repr_line_.setVisibility(false);
		  repr_surface_.setVisibility(false);

		  
		  o.autoView();
		  callback();
		});
	});

}
//clear stage
function clear_stage(){
	stage_.removeAllComponents();
}

//spin model
function set_spin(value){
	stage_.setSpin(value);
}
/*representation control below*/
function set_repr_line(value){
	repr_line_.setVisibility(value);
}

function set_repr_ball_stick(value){
	repr_ball_stick_.setVisibility(value);
}

function set_repr_surface(value){
	repr_surface_.setVisibility(value);
}

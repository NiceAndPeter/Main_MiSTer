# Usage:
#   vivado -mode batch -source scripts/vivado/te0802_bootstrap.tcl -tclargs <output_dir>

set out_dir "build/te0802_bootstrap"
if {$argc >= 1} {
    set out_dir [lindex $argv 0]
}

file mkdir $out_dir
set proj_dir [file normalize "$out_dir/proj"]
set proj_name "te0802_mister_port"

# TODO: Replace with the exact TE0802 FPGA part once module variant is finalized.
set target_part "xczu3eg-sbva484-1-e"

if {[file exists $proj_dir]} {
    puts "INFO: Removing previous project directory: $proj_dir"
    file delete -force $proj_dir
}

create_project $proj_name $proj_dir -part $target_part

# Keep this minimal at bootstrap stage; sources are added after mapping and wrapper decisions.
set_property target_language Verilog [current_project]
set_property default_lib xil_defaultlib [current_project]

set fp [open "$out_dir/bootstrap_summary.txt" "w"]
puts $fp "project_name=$proj_name"
puts $fp "project_dir=$proj_dir"
puts $fp "target_part=$target_part"
puts $fp "vivado_version=[version -short]"
close $fp

puts "INFO: Bootstrap project created successfully."
close_project
exit 0
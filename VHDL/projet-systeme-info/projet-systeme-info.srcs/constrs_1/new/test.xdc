create_clock -period 10.000 -name CLK -waveform {0.000 5.000} [get_ports CLK]
#Horloge avec un oscillateur
set_property -dist { PACKAGE_PIN W5 IOSTANDARD LVCMOS33 } [get_ports {
CLK } ]
create_clock -add -name sysclk_pin -period 10.00 -waveform { 0 5 } [get_ports {
CLK } ]
# Signal binaire
set_property -dict {PACKAGE_PIN N1 IOSTANDARD LVCMOS33} [get_ports
RST]
# Signal vectoriel
set_property -dict {PACKAGE_PIN N2 IOSTANDARD LVCMOS33} [get_ports
{FAUSSE_SORTIE[0]}]
set_property -dict {PACKAGE_PIN N2 IOSTANDARD LVCMOS33} [get_ports
{FAUSSE_SORTIE[1]}]
set_property -dict {PACKAGE_PIN N2 IOSTANDARD LVCMOS33} [get_ports
{FAUSSE_SORTIE[2]}]
set_property -dict {PACKAGE_PIN N2 IOSTANDARD LVCMOS33} [get_ports
{FAUSSE_SORTIE[3]}]
set_property -dict {PACKAGE_PIN N2 IOSTANDARD LVCMOS33} [get_ports
{FAUSSE_SORTIE[4]}]
set_property -dict {PACKAGE_PIN N2 IOSTANDARD LVCMOS33} [get_ports
{FAUSSE_SORTIE[5]}]
set_property -dict {PACKAGE_PIN N2 IOSTANDARD LVCMOS33} [get_ports
{FAUSSE_SORTIE[6]}]
set_property -dict {PACKAGE_PIN N2 IOSTANDARD LVCMOS33} [get_ports
{FAUSSE_SORTIE[7]}]
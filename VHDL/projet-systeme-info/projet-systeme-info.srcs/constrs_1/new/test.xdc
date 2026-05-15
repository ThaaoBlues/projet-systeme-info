# Configuration de l'horloge unique (100 MHz)
create_clock -period 1500.000 -name sysclk_pin -waveform {0.000 5.000} [get_ports CLK]
set_property -dict { PACKAGE_PIN W5 IOSTANDARD LVCMOS33 } [get_ports CLK]

# Signal binaire Reset
set_property -dict {PACKAGE_PIN W19 IOSTANDARD LVCMOS33} [get_ports RST]

# Signaux vectoriels : Chaque bit doit avoir un PACKAGE_PIN unique !
# (Exemple basé sur les LED 0 à 7 d'une Basys 3)
set_property -dict {PACKAGE_PIN U16 IOSTANDARD LVCMOS33} [get_ports {FAUSSE_SORTIE[0]}]
set_property -dict {PACKAGE_PIN E19 IOSTANDARD LVCMOS33} [get_ports {FAUSSE_SORTIE[1]}]
set_property -dict {PACKAGE_PIN U19 IOSTANDARD LVCMOS33} [get_ports {FAUSSE_SORTIE[2]}]
set_property -dict {PACKAGE_PIN V19 IOSTANDARD LVCMOS33} [get_ports {FAUSSE_SORTIE[3]}]
set_property -dict {PACKAGE_PIN W18 IOSTANDARD LVCMOS33} [get_ports {FAUSSE_SORTIE[4]}]
set_property -dict {PACKAGE_PIN U15 IOSTANDARD LVCMOS33} [get_ports {FAUSSE_SORTIE[5]}]
set_property -dict {PACKAGE_PIN U14 IOSTANDARD LVCMOS33} [get_ports {FAUSSE_SORTIE[6]}]
set_property -dict {PACKAGE_PIN V14 IOSTANDARD LVCMOS33} [get_ports {FAUSSE_SORTIE[7]}]
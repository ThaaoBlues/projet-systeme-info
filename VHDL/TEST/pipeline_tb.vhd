library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- L'entité du Testbench est vide
entity pipeline_tb is
end pipeline_tb;

architecture Behavioral of pipeline_tb is

    -- Composant à tester (Unit Under Test)
    component pipeline
        Port ( CLK : in STD_LOGIC; RST : in STD_LOGIC );
    end component;

    -- Signaux internes pour le test
    signal clk_tb : std_logic := '0';
    signal rst_tb : std_logic := '0';

    -- Période de l'horloge (100 MHz -> 10ns)
    constant CLK_PERIOD : time := 10 ns;

begin

    -- Instanciation de l'UUT
    -- Note : Si ton entité pipeline reste vide, on l'instancie sans port map
    uut: pipeline port map(CLK=>clk_tb, RST=>rst_tb) ; 

    -- Génération de l'horloge
    clk_process : process
    begin
        while now < 1000 ns loop -- Simule pendant 1000ns
            clk_tb <= '0';
            wait for CLK_PERIOD / 2;
            clk_tb <= '1';
            wait for CLK_PERIOD / 2;
        end loop;
        wait;
    end process;

    -- Stimulus : Test de l'AFC
    -- On part du principe que la ROM contient une instruction AFC : 
    -- Format supposé : OP=06, A=Adresse_Reg, B=Valeur_Immédiate
    stim_proc: process
    begin		
        -- Initialisation
        rst_tb <= '0';
        wait for 20 ns;	
        
        -- Relâchement du reset
        rst_tb <= '1';
        
        -- L'instruction AFC va mettre plusieurs cycles à traverser le pipeline :
        -- Cycle 1 : LI/DI (Lecture instruction dans ROM)
        -- Cycle 2 : DI/EX (Décodage et passage vers EX)
        -- Cycle 3 : EX/MEM (Passage vers MEM)
        -- Cycle 4 : MEM/RE (Passage vers Write Back)
        -- Cycle 5 : Ecriture effective dans le banc de registres
        
        wait for CLK_PERIOD * 10;

        report "Fin de simulation du test AFC";
        wait;
    end process;

end Behavioral;

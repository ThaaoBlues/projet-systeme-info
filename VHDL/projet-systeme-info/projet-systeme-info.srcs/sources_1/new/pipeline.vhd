----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/25/2026 12:53:11 PM
-- Design Name: 
-- Module Name: pipeline - Structural
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity pipeline is
    Port (
        CLK : in std_logic;
        RST : in std_logic;
        FAUSSE_SORTIE : out std_logic_vector(7 downto 0)
    );
end pipeline;

architecture Structural of pipeline is

component ROM port(
        ADDR : in std_logic_vector( 7 downto 0);
        CLK : in std_logic;
        SORTIE : out std_logic_vector(31 downto 0)
);
end component;


component LIDI port(
        CLK : in std_logic;
        INST : in std_logic_vector(31 downto 0);
        OP,A,B,C   : out std_logic_vector(7 downto 0)
    );
end component;


component BANC_REG port(
        ADDR_A,ADDR_B,ADDR_W : in std_logic_vector(3 downto 0);
        W      : in std_logic;
        DATA   : in std_logic_vector(7 downto 0);
        RST    : in std_logic;
        CLK    : in std_logic;
        QA,QB  : out std_logic_vector(7 downto 0) --n des aléas -
         

    
    );
end component;

component MUX_BR port(
out_br : in std_logic_vector(7 downto 0);
    out_li_di : in std_logic_vector(7 downto 0);
    op_code : in std_logic_vector(7 downto 0);
    out_mux_br : out std_logic_vector(7 downto 0) 
    );
end component;



component DIEX port(
        CLK : in std_logic;
        OP_IN, A_IN, B_IN, C_IN: in std_logic_vector(7 downto 0);
        OP_OUT, A_OUT, B_OUT, C_OUT: out std_logic_vector(7 downto 0)
    );
end component;

-- je pense que là c'est juste 3 registres
component EXMEM port(
        CLK : in std_logic;
        OP_IN, A_IN, B_IN: in std_logic_vector(7 downto 0);
        OP_OUT, A_OUT, B_OUT: out std_logic_vector(7 downto 0)
    );
end component;


-- là jsp c'est un peu plus complexe comme il touche au banc de registres
component MEMRE port(
        CLK : in std_logic;
        OP_IN, A_IN, B_IN: in std_logic_vector(7 downto 0);
        OP_OUT, A_OUT, B_OUT: out std_logic_vector(7 downto 0)
    );
end component;


component ALU_COMP
    Port(
        CLK : in std_logic;
        B, A : in  std_logic_vector(7 downto 0);
        S : out std_logic_vector(7 downto 0);
        Ctrl_ALU : in std_logic_vector(2 downto 0);
        Carry,Overflow,Negatif,Zero : out std_logic
    );
end component;

component LC_UAL
    port(op : in std_logic_vector (7 downto 0);
         ctrl_out : out std_logic_vector(2 downto 0));
end component;

component MUX_UAL
    port(out_ual : in std_logic_vector(7 downto 0);
    out_di_ex : in std_logic_vector(7 downto 0);
    op_code : in std_logic_vector(7 downto 0);
    out_mux_ual : out std_logic_vector(7 downto 0) );
end component ;

component DATA_MEM_COMP
    PORT (
        ADDR   : in std_logic_vector(7 downto 0);
        ENTREE : in std_logic_vector( 7 downto 0);
        RW     : in std_logic;
        RST    : in std_logic;
        CLK    : in std_logic;
        SORTIE : out std_logic_vector(7 downto 0)
    );
end component;

component LC_MEM 
    PORT( op : in std_logic_vector (7 downto 0);
            rw_out : out std_logic);
end component ;

component LC_RE
    PORT( op : in std_logic_vector (7 downto 0);
        w_out : out std_logic);
        end component;
        
component MUX_EX_MEM_TO_MEM is
 Port ( op, ex_mem_a, ex_mem_b : in std_logic_vector(7 downto 0); out_addr : out std_logic_vector(7 downto 0));
end component;


component MUX_DATA_MEM is
     Port ( 
     op : in std_logic_vector(7 downto 0);
     out_data_mem : in std_logic_vector(7 downto 0);
     out_ex_mem : in std_logic_vector(7 downto 0);
     out_b : out std_logic_vector(7 downto 0)
     );
end component;


component retard_B_ALU is 
    Port ( 
            Clk : in std_logic;
            B : in std_logic_vector(7 downto 0);
            B_out : out std_logic_vector(7 downto 0) );

end component;


for all: ROM use entity work.ROM(beh);
for all: LIDI use entity work.LIDI(beh);
for all: BANC_REG use entity work.BANC(beh);
for all: DIEX use entity work.DIEX(beh);
for all: EXMEM use entity work.EXMEM(beh);
for all: MEMRE use entity work.MEMRE(beh);
for all: ALU_COMP use entity work.ALU(beh);
for all: DATA_MEM_COMP use entity work.DATA_MEM(beh);
for all: LC_RE use entity work.LC_RE(Behavioral);
for all: MUX_BR use entity work.MUX_BR(Behavioral);
for all: LC_UAL use entity work.LC_UAL(Behavioral);
for all: MUX_UAL use entity work.MUX_UAL(Behavioral);
for all: LC_MEM use entity work.LC_MEM(Behavioral);
for all: MUX_DATA_MEM use entity work.MUX_DATA_MEM(Behavioral);
for all: MUX_EX_MEM_TO_MEM use entity work.mux_ex_mem_to_mem(Behavioral);
for all: retard_B_ALU use entity work.retard_B_alu(Behavioral);






signal ip : std_logic_vector(7 downto 0) := (others => '0');

-- sortie ROM
signal inst_4o : std_logic_vector(31 downto 0) := (others => '0');

-- sortie LI/DI
signal op_li_di, a_li_di, b_li_di, c_li_di : std_logic_vector(7 downto 0);

-- sortie banc de registres principaux (on utilise pas pour afc encore)
signal qa_out, qb_out : std_logic_vector(7 downto 0);

-- sortie DI/EX
signal op_di, a_di, b_di, c_di : std_logic_vector(7 downto 0);

-- sortie EX/MEM
signal op_ex, a_ex, b_ex : std_logic_vector(7 downto 0);

-- sortie MEM/RE
signal op_re, a_re, b_re : std_logic_vector(7 downto 0);


-- sortie ALU
signal alu_out : std_logic_vector(7 downto 0);
signal s_carry : std_logic;
signal s_overflow : std_logic;
signal s_zero : std_logic;
signal s_negatif : std_logic;


-- sortie memoire donnees
signal data_mem_out : std_logic_vector(7 downto 0);

--LC banc registre
signal w_out_br : std_logic;

--mux banc registre
signal out_mux_br :std_logic_vector(7 downto 0);

-- LC ual
signal lc_ctrl_ual : std_logic_vector(2 downto 0);

--mux UAL
signal out_mux_ual :std_logic_vector(7 downto 0); 

-- LC mem
signal lc_mem_out : std_logic;

-- mux data mem
signal mux_data_mem_out : std_logic_vector(7 downto 0);

-- mux mux_ex_mem_to_mem
signal mux_ex_mem_to_mem_out : std_logic_vector(7 downto 0);

-- signaux pour créer un retard artificiel afin de synchro avec les deux étages de l'alu.
signal op_di_r1 : std_logic_vector(7 downto 0);
signal a_di_r1  : std_logic_vector(7 downto 0);
signal op_di_r2 : std_logic_vector(7 downto 0);
signal a_di_r2  : std_logic_vector(7 downto 0);

signal b_en_retard : std_logic_vector(7 downto 0);



begin

-- LES MULTIPLEXERS SERONT DES COMPOSANTS   
    mem_code : ROM port map(ADDR=>ip,CLK=>CLK,SORTIE=>inst_4o);
    
    
-- LI/DI
    li_di : LIDI port map(
                            CLK => Clk,
                           INST=>inst_4o,
                          OP=>op_li_di,
                          A=>a_li_di,
                          B=>b_li_di,
                          C=>c_li_di
                        );


    banc_registres_principal : BANC_REG port map(
        ADDR_A => b_li_di(3 downto 0),
        ADDR_B => c_li_di(3 downto 0),
        ADDR_W => a_re(3 downto 0), -- TODO: à relier à la sortie a_re
        W      => w_out_br,    -- TODO : à relier au controleur en fonction de op_re
        DATA   => b_re,  -- TODO : à relier à la sortie b_re
        RST    => rst,
        CLK    => CLK,
        QA     => qa_out,
        QB     => qb_out
    );
    
    lc_registre : LC_RE port map(
        op => op_re,
        w_out => w_out_br);
        
    mux_registre : MUX_BR port map(
    out_br => qa_out,
    out_li_di => b_li_di,
    op_code => op_li_di,
    out_mux_br => out_mux_br);
        


-- ATTENTION : les sorties LI/DI sont branchées sur di_ex
-- mais on va devoir bancher le banc de registres entre les deux
-- donc il va falloir séparer sortie li_di et signaux en entrée de DIEX 
-- on va donc mettre des mux partout presque
-- ce sera la même pour tous les étages

-- je pense que les mux sont faisable avec des 'when' directement en fonction de l'OP
-- sans forcément besoin de composant

-- DI/EX
    alu : alu_comp port map(
    
                       CLK => CLK,
                       A => b_di,
                       B => c_di,
                       Ctrl_ALU => lc_ctrl_ual, --  passer par le controleur avant ici 
                       S => alu_out,
                       Carry => s_carry,
                       Overflow=> s_overflow,
                       Negatif=> s_negatif,
                       Zero=> s_zero 
                    );
                    
    lc_alu : lc_ual port map(
        op => op_di,
        ctrl_out => lc_ctrl_ual
    );
    
    
    retardateur_b : retard_B_alu port map(
        CLK => CLK,
        B => b_di,
        B_out => b_en_retard
    
    );
    
    mux_alu : mux_ual port map(
             out_ual => alu_out,
        out_di_ex =>  b_en_retard,
        op_code => op_di_r2,
        out_mux_ual => out_mux_ual);


    
    di_ex : DIEX port map(
                                CLK => CLK,
                                OP_IN => op_li_di, 
                                A_IN => a_li_di, 
                                B_IN => out_mux_br, -- mux entre b_li_di,qa_out suivant op_li_di
                                C_IN => qb_out, --  relier directement à qb du banc de registre
                                OP_OUT => op_di, 
                                A_OUT => a_di, 
                                B_OUT => b_di, 
                                C_OUT => c_di
                            );

-- EX/MEM

    ex_mem : EXMEM port map(
                                CLK => CLK,
                                OP_IN => op_di_r2, 
                                A_IN => a_di_r2,
                                B_IN => out_mux_ual, -- : mux entre sortie d'ALU, b_di suivant op_di
                                OP_OUT => op_ex, 
                                A_OUT => a_ex, 
                                B_OUT => b_ex
                            );

-- MEM/RE

    mux_ex_mem_to_mem_component : MUX_EX_MEM_TO_MEM port map( op => op_ex, ex_mem_a => a_ex, ex_mem_b => b_ex, out_addr =>mux_ex_mem_to_mem_out);
    


    data_mem : DATA_MEM_COMP port map(ADDR => mux_ex_mem_to_mem_out, --  mux entre b_ex, a_ex en fonction de op_ex
                                 ENTREE => b_ex, 
                                 RW => lc_mem_out, -- c'est le controleur, en fonction de op_ex
                                 CLK => CLK, 
                                 SORTIE => data_mem_out,
                                 RST => RST
                                );
                                
    lc_data_mem : LC_MEM port map( op => op_ex,
            rw_out => lc_mem_out);
            
    mux_data : MUX_DATA_MEM port map( op => op_ex, out_data_mem => data_mem_out, out_ex_mem => b_ex,out_b => mux_data_mem_out);


    mem_re : MEMRE port map( 
                            CLK => CLK,
                            OP_IN => op_ex, 
                            A_IN => a_ex, 
                            B_IN => mux_data_mem_out, -- : mux entre b_ex,data_mem_out suivant op_ex 
                            OP_OUT => op_re, 
                            A_OUT => a_re, 
                            B_OUT => b_re
                        );

-- process d'incrémentation de IP
    process(CLK) begin
        if RST = '0' then
         ip <= (others => '0');
        elsif CLK'Event AND CLK='1' then 
            ip <= std_logic_vector( unsigned(ip) + 1 ); 
        end if;
    end process;
    
    process(CLK) 
    
    begin
         --créer le retard artificiel de 2 cycles
        
        if rising_edge(CLK) then
            op_di_r1 <= op_di;
            a_di_r1  <= a_di;
            op_di_r2 <= op_di_r1;
            a_di_r2 <= a_di_r1;
        end if;
    end process;


    FAUSSE_SORTIE <= b_re;

end Structural;



-- LES REGISTRES DE PIPELINE VONT RESSEMBLER A CA
-- SAUF LE PREMIER ET DERNIER YA DES TRUCS EN PLUS PEUT-ETRE
-- entity DIEX is
--     Port ( CLK : in STD_LOGIC;
--            OP_IN, A_IN, B_IN, C_IN : in STD_LOGIC_VECTOR (7 downto 0);
--            OP_OUT, A_OUT, B_OUT, C_OUT : out STD_LOGIC_VECTOR (7 downto 0));
-- end DIEX;

-- architecture Behavioral of DIEX is
-- begin
--     process(CLK) begin
--         if rising_edge(CLK) then
--             OP_OUT <= OP_IN; A_OUT <= A_IN; B_OUT <= B_IN; C_OUT <= C_IN;
--         end if;
--     end process;
-- end Behavioral;


Systém má za úkol spravovat skladové zásoby. Tím je myšleno příjem vstupních surovin jejich zpracování a oddělení procentuálního odpadu a výsledný prodej. To zároveň zahrnuje uchovávání a logování účetnictví včetně EET.

Pateřním systémem je databázový systém. Pro licencování a bezplatné použití byl zvolen databázový systém MySQL. Na tuto databázi jsou připojeni klienti. Klienti se dělí do dvou skupin:
* Pokladní systém
* Skladový systém


Pokladní systém běží na samostatném počítači opatřeném termotiskárnou a dotikovým monitorem ze kterého je možné provádět drobné prodeje. 
Skladový systém může bežet na stejném počítači jako databázový systém, ale také na jakémkoli počítači v síti. Skladový systém má za úkol spravovat skladový majetek a vytvářet faktury pro větší prodeje.

Od každého klienta může být spuštěno libovolné množství klientů na libovolném množství počítačů. To zároveň vyžaduje nutnost synchronizace přístupu k databázi.


		|------- CASHDESK ----CASHDESK_CLIENT 1
		|		  |
		|		  |---CASHDESK_CLIENT 2
		|		  |
		|		  |---CASHDESK_CLIENT 3
		|
DATABASE -------|
		|
		|
		|
		|
		|
		|-------STOCK -----STOCK_CLIENT 1
			      |
			      |----STOCK_CLIENT 2
			      |
			      |----STOCK_CLIENT 3





Architekturua je rozdělena do čtiř částí (vrstev):
* TRANSVRSTVA - společná vrstva která obsahuje kód viditelný ve šech vrstvách
* CONTROLER - logika programu
* VIEW - prezentační vrstva s grafickým uživatelským rozhraním
* MAIN -  hlavní víkonné vlákno programu


moduly alarm buffer, alarm widget a alarm tvoří architekturu model-view-controler kde alarm buffer je model, alarm widget je view a alarm tvoří controler.  



Rezervované IP adresy:

Pokladna: 192.168.1.10
Správa skladu (databáze): 192.168.1.11




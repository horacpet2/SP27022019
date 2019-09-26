

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
		|------- STOCK -----STOCK_CLIENT 1
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


Důležité je aby se nějakou dobu používaly oba systémy (nový i starý), nový systém poběží nějakou dobu v testovacím režimu a v případě chyby se může získat záloha ze starého systému. Po odladění všech nedostatků se bude moct přejít naplno na nový systém

Požadavkem je aby bylo možné obilí a mouku dynamicky menedžovat. Občas je přivezeno obilí, které jde pouze na semletí. To znamená že je třeba zaznamenat přesné množství obilí které ve vlastnictví jiného člověka
Řešením jsou virtuální sila. Virtuální sila jsou skladovací jednotky s obilím a semletou moukou. Jedná se o obdobu fyzických sil ve kterých se skladuje obilí a semletá mouka, díky tomu je snazší se v tomto orientovat.
Každé silo má datové atributy: ID, jméno sila, druh obilí/mouky/otrub, produkt (obilí/kouka/otruby) , množství, poznámka
Tato sila se nachízejí v jedné databázové tabulce do které lze dynamicky přidávat nebo odebírat virtuální sila.
Každé silo má příznak, který určuje co se v něm nachízí a podle toho nabízí určité funkce.
- semlýt (obilí)
- napytlovat (obilí/mouka, otruby) (kolik pytlů s jakou váhou)
- vyhodit (obilí/mouka/otruby)
- prodat (obilí/mouka/otruby)
- přesunout (obilí/mouka/otruby)

v programu je nastaven seznam produktů se kterými je ve mlýně manypulováno, každé silo tak má nastaveno co je uvnitř, a mezi jednotlivými sili lze obsah přesouvat ale pouze v případě, že je uvnitř obsah stejný.

Při pytlování se zadá kolik pytlů se napytlovalo s jakou váhou, automaticky se odečte dané množství ze sila a počet pytlů se uloží do databázové tabulky pro pokladní systém

Jednotlivé transakce ať z pokladního systému tak přes faktury se ukládají do databázové tabulky s transakcemi. Tam je zároveň označeno zda byla transakce provedena přes fakturu nebo přes pokladní systém s EET. Z této databáze bude možné znovu zrekonstruovat účtekny s údaji EET pro účetnictví, takže není nutné vždy tisknout účtenku dvakrát (vícekrát).

Fakturou lze brát produkty jak z virtuálních sil tak ze skladu s pytli.


Je třeba zajistit, aby se při načítání položek do manualního vstupu nahrály všechny položky korektně (díry v intervalech ID) -> je třeba udržet ID konzistentní, to je třeba zajistit v programu pro správu majetku


** TODO **

* napojit výslednou cenu do obrazovky s objednávkou
* vytvořit rozhraní pro vyčítání parametrů položky objednávky z databáze
* napojit cenu objednávky do obrazovky s dokončením objednávky
* napojit kalulátor na počítání s cenou objednávky
* generování kódu pro tisk účtenky
* odesílání kódu účtenky do tiskárny
* napojení databáze
* vytvořit strukturu databáze

** DONE **

* napojit inkrementaci na tlačítku v obrazovce objednávek
* napojit dekrementaci na tlačítko v obrazovce objednávek
* napojit vyčištění objednávky na tlačítko v obrazovce objednávek
* vytvořit funkcionalitu na označení položek v seznamu
* přidat skrolování do seznamu
























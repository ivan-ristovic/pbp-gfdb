INSERT INTO Guild VALUES
  (203145877996897589, DEFAULT, ';'),
  (314527785497547896, 'Very advanced guild', DEFAULT),
  (303620791969513473, DEFAULT, DEFAULT),
  (456453132154897956, 'My guild', DEFAULT),
  (513212312154564896, DEFAULT, DEFAULT),
  (132123132154879799, 'Test', '!>'),
  (079784454115466998, DEFAULT, DEFAULT),
  (074512113355456879, DEFAULT, DEFAULT),
  (332114455123335468, DEFAULT, '.'),
  (213134544778532212, DEFAULT, '.'),
  (411245333322145569, 'My guild name', DEFAULT),
  (065465132148799999, DEFAULT, DEFAULT);


INSERT INTO Korisnik VALUES
  (031124666545222133, 'Someone'),
  (225433321245566879, DEFAULT),
  (122933244875566554, DEFAULT),
  (542311224556452112, 'Tester'),
  (102011122301221030, DEFAULT),
  (142000012420233640, 'Troublemaker'),
  (422001221133220000, 'Admin'),
  (222103332120154202, DEFAULT);


INSERT INTO Kanal VALUES
  (321112324455666652, 203145877996897589, 'text', DEFAULT),
  (225433321245566879, 314527785497547896, 'category', 'My Category'),
  (225433321245569879, 314527785497547896, 'text', DEFAULT),
  (225433321245560879, 314527785497547896, 'voice', DEFAULT),
  (122233244875566554, 303620791969513473, 'text', DEFAULT),
  (542311224556452112, 456453132154897956, 'text', DEFAULT),
  (102011122301221030, 513212312154564896, 'text', 'Test'),
  (142000012420233640, 132123132154879799, 'text', DEFAULT),
  (422001221133220000, 079784454115466998, 'text', DEFAULT),
  (222103332120154202, 074512113355456879, 'text', DEFAULT),
  (102511122301221030, 332114455123335468, 'text', 'Test channel'),
  (142500012420233640, 213134544778532212, 'text', DEFAULT),
  (422501221133220000, 411245333322145569, 'text', DEFAULT),
  (222503332120154202, 065465132148799999, 'text', DEFAULT);


INSERT INTO Ban VALUES
  (142000012420233640, 314527785497547896, 422001221133220000, DEFAULT, 'I don\'t like this guy.');


INSERT INTO Clan_Guilda VALUES
  (422001221133220000, 314527785497547896, '20171006', 128),
  (422001221133220000, 303620791969513473, '20171108', DEFAULT),
  (225433321245566879, 314527785497547896, '20160521', DEFAULT),
  (222103332120154202, 314527785497547896, '20161201', DEFAULT),
  (122933244875566554, 411245333322145569, '20170101', DEFAULT),
  (122933244875566554, 314527785497547896, '20171006', DEFAULT);


INSERT INTO Clan_Kanala VALUES
  (422001221133220000, 314527785497547896, 225433321245569879, 128),
  (422001221133220000, 303620791969513473, 122233244875566554, 4),
  (225433321245566879, 314527785497547896, 225433321245569879, 4),
  (222103332120154202, 314527785497547896, 225433321245569879, 4),
  (122933244875566554, 411245333322145569, 422501221133220000, 2),
  (122933244875566554, 314527785497547896, 225433321245569879, 0);


INSERT INTO Emoji VALUES
  ('pepe', 314527785497547896, 422001221133220000, '20171101', '?');


INSERT INTO Filter VALUES
  (1, 314527785497547896, 'fuck');


INSERT INTO Zadatak VALUES
  (1, 'some content', '2018-01-01 00:00:00');

INSERT INTO routes
VALUES (1,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA","6393F82F-4687-433D-AA23-1966330381FE","CreditReport",0x01),
(2,"556E2EAA-1D5B-5BC0-BCC4-4CEB669408DA","6323D82F-4687-433D-AA23-1966330381FE","DebitReport",0x01),   
(3,"666E2EAA-1D5B-5BC0-BCC4-4CEB669408DA","8323D82F-4687-433D-AA23-1966330381FE", "DebitReport",0x01);        


INSERT INTO transform_config
VALUES (1001,1,"Json_transform","json"),
(1002,2,"Json_transform","json"),
(1003,3,"Json_transform","json");

INSERT INTO transport_config
VALUES (2001,1,"https://ifsc.razorpay.com/","HTTP"),
(2002,2,"testraavi1@gmail.com","email"),
(2003,3,"https://ifsc.razorpay.com/","HTTP");

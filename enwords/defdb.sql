CREATE TABLE enwords (
    id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    en VARCHAR(100) NOT NULL,
    ja VARCHAR(100) NOT NULL,
    finish BOOLEAN DEFAULT false
);
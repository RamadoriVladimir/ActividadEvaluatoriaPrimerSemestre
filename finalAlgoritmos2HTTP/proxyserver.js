const express = require('express');
const cors = require('cors');
const { createProxyMiddleware } = require('http-proxy-middleware');

const app = express();
const PORT = 18059; 
const TARGET_API_URL = 'http://localhost:18080'; 

app.use(cors({
    origin: '*',
    methods: ['GET', 'POST', 'OPTIONS'],
    allowedHeaders: ['Content-Type']
}));

app.use('/api', createProxyMiddleware({
    target: TARGET_API_URL,
    changeOrigin: true, 
    pathRewrite: {
        '^/api': '/', 
    },
    onProxyReq: (proxyReq, req, res) => {
        console.log(`[Proxy] Reenviando ${req.method} ${req.originalUrl} a ${proxyReq.path}`);
    },
    onProxyRes: (proxyRes, req, res) => {
        console.log(`[Proxy] Recibida respuesta ${proxyRes.statusCode} para ${req.originalUrl}`);
    },
    onError: (err, req, res) => {
        console.error('[Proxy] Error en el proxy:', err);
        res.status(500).send('Error en el servidor proxy.');
    }
}));

app.use(express.static(__dirname));

app.listen(PORT, () => {
    console.log(`Servidor proxy escuchando en http://localhost:${PORT}`);
    console.log(`Las solicitudes a http://localhost:${PORT}/api/* serán reenviadas a ${TARGET_API_URL}/*`);
    console.log(`Abre tu navegador en http://localhost:${PORT}/client.html`);
});

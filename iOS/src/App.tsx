import React from 'react';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';
import IntersectObserver from '@/components/common/IntersectObserver';
import { Toaster } from '@/components/ui/sonner';
import { SettingsProvider } from '@/contexts/SettingsContext';

import { routes } from './routes';

const App: React.FC = () => {
  return (
    <Router>
      <SettingsProvider>
        <IntersectObserver />
        <Routes>
          {routes.map((route, index) => (
            <Route
              key={index}
              path={route.path}
              element={route.element}
            />
          ))}
          <Route path="*" element={<Navigate to="/" replace />} />
        </Routes>
        <Toaster position="top-center" />
      </SettingsProvider>
    </Router>
  );
};

export default App;

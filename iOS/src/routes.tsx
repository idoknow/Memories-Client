import StatusCheckPage from './pages/StatusCheckPage';
import GalleryPage from './pages/GalleryPage';
import type { ReactNode } from 'react';

export interface RouteConfig {
  name: string;
  path: string;
  element: ReactNode;
  visible?: boolean;
  /** Accessible without login. Routes without this flag require authentication. Has no effect when RouteGuard is not in use. */
  public?: boolean;
}

export const routes: RouteConfig[] = [
  {
    name: '服务状态',
    path: '/',
    element: <StatusCheckPage />,
    public: true,
  },
  {
    name: '图片浏览',
    path: '/gallery',
    element: <GalleryPage />,
    public: true,
  },
];
